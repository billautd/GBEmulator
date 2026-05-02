#include <PPU.h>
#include <Context.h>
#include <Interrupts.h>

#define PPU_DEBUG false

PPU::PPU(Context &ctx) : ctx(ctx)
{
}

PPU::~PPU()
{
}

void PPU::init()
{
    cycles = 0;
    lineTicks = 0;
    frame = 0;
    setLY(0);
    setMode(2);
}

void PPU::tick()
{
    cycles++;
    lineTicks++;
    u8 mode = getMode();
    switch (mode)
    {
    case PPU_MODES::HBLANK:
        hblank();
        break;
    case PPU_MODES::VBLANK:
        vblank();
        break;
    case PPU_MODES::OAM_SCAN:
        oamScan();
        break;
    case PPU_MODES::DRAWING_PIXELS:
        drawPixels();
        break;
    default:
        std::cerr << std::format("Unknown PPU mode {}\n", getMode());
        ctx.setRunning(false);
        break;
    }
#if PPU_DEBUG
    std::cout << std::format("Cycle {}, mode {}, ly {}\n", cycles, getMode(), getLY());
#endif
}

void PPU::hblank()
{
    if (lineTicks >= TICKS_PER_LINE)
    {
        lineTicks = 0;
        incrementLY();
        if (getLY() > 143)
        {
            setMode(PPU_MODES::VBLANK);
            ctx.cpu().getInterrupts().requestInterrupt(InterruptType::INT_VBLANK);
        }
        else
            setMode(PPU_MODES::OAM_SCAN);
    }
}

void PPU::vblank()
{
    if (lineTicks >= TICKS_PER_LINE)
    {
        lineTicks = 0;
        incrementLY();
        if (getLY() > LINES_PER_FRAME)
        {
            setLY(0);
            frame++;
            setMode(PPU_MODES::OAM_SCAN);
        }
    }
}

void PPU::oamScan()
{
    if (lineTicks > 80)
    {
        setMode(PPU_MODES::DRAWING_PIXELS);
    }
}

void PPU::drawPixels()
{
    if (lineTicks > 172)
    {
        setMode(PPU_MODES::HBLANK);
    }
}

void PPU::createTile(int x, int y, int tileIndex, int scale, SDL_Surface *surface)
{
    SDL_Rect rect;
    for (int i = 0; i < 16; i += 2)
    {
        int offset = tileIndex * 16;
        u8 colorData1 = ctx.mem().getMem().at(0x8000 + offset + i);
        u8 colorData2 = ctx.mem().getMem().at(0x8001 + offset + i);
        for (int bit = 7; bit >= 0; bit--)
        {
            u8 color1 = (colorData1 >> bit) & 1;
            u8 color2 = (colorData2 >> bit) & 1;

            rect.x = x + (scale * (7 - bit));
            rect.y = y + (scale * (i / 2));
            rect.w = scale;
            rect.h = scale;
            SDL_FillSurfaceRect(surface, &rect, colors[(color1 << 1) | color2]);
        }
    }
}

u8 PPU::getLY()
{
    return ctx.mem().readMem(LY_ADDR);
}

void PPU::setLY(u8 ly)
{
    ctx.mem().writeMem(LY_ADDR, ly);
}

void PPU::incrementLY()
{
    setLY(getLY() + 1);
}

u8 PPU::getMode()
{
    return ctx.mem().readMem(STAT_ADDR) & 0b11;
}

void PPU::setMode(u8 mode)
{
    // Reset last 2 bits and set new bits
    ctx.mem().writeMem(STAT_ADDR, (ctx.mem().readMem(STAT_ADDR) & 0b11111100) + mode);
}