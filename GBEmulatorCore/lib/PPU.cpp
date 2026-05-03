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
    case PPUModes::HBLANK:
        hblank();
        break;
    case PPUModes::VBLANK:
        vblank();
        break;
    case PPUModes::OAM_SCAN:
        oamScan();
        break;
    case PPUModes::DRAWING_PIXELS:
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
            setMode(PPUModes::VBLANK);
            ctx.cpu().getInterrupts().requestInterrupt(InterruptType::INT_VBLANK);
        }
        else
            setMode(PPUModes::OAM_SCAN);
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
            setMode(PPUModes::OAM_SCAN);
        }
    }
}

void PPU::oamScan()
{
    // Do one OAM scan every other dot, to space out within 80 dots
    // Line tick 0 == 0xFE00-0xFE03
    // Line tick 2 == 0xFE04 - 0xFE07
    //...
    // Line tick 78 == 0xFE9C - 0xFE9F
    // Line tick n = (0xFE00 + lineTick * 2) - (0xFE03 + lineTick * 2)
    if (lineTicks % 2 == 0)
    {
        u8 yPos = ctx.mem().readMem(0xFE00 + lineTicks * 2);
        u8 xPos = ctx.mem().readMem(0xFE01 + lineTicks * 2);
        u8 tileIndex = ctx.mem().readMem(0xFE02 + lineTicks * 2);
        u8 flags = ctx.mem().readMem(0xFE03 + lineTicks * 2);
        // std::cout << (int)ctx.mem().readMem(0xFF45) << " ";
    }

    if (lineTicks >= 80)
    {
        setMode(PPUModes::DRAWING_PIXELS);
    }
}

void PPU::drawPixels()
{
    if (lineTicks >= 172)
    {
        setMode(PPUModes::HBLANK);
    }
}

void PPU::createTile(int x, int y, int tileIndex, SDL_Surface *surface)
{
    if (surface == nullptr)
        return;
    SDL_Rect rect;
    for (int i = 0; i < 16; i += 2)
    {
        int offset = tileIndex * 16;
        u8 colorData1 = ctx.mem().readMem(0x8000 + offset + i);
        u8 colorData2 = ctx.mem().readMem(0x8001 + offset + i);
        for (int bit = 7; bit >= 0; bit--)
        {
            u8 color1 = (colorData1 >> bit) & 1;
            u8 color2 = (colorData2 >> bit) & 1;

            rect.x = x + (UI::SCALE * (7 - bit));
            rect.y = y + (UI::SCALE * (i / 2));
            rect.w = UI::SCALE;
            rect.h = UI::SCALE;
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

u8 PPU::getLYC()
{
    return ctx.mem().readMem(LYC_ADDR);
}

// void PPU::setLCDStatus(LCDStatuses status, bool active)
// {
//     if (active)
//         ctx.mem().writeMem(STAT_ADDR, (Common::setBit(ctx.mem().readMem(STAT_ADDR), status)));
//     else
//         ctx.mem().writeMem(STAT_ADDR, (Common::resetBit(ctx.mem().readMem(STAT_ADDR), status)));
// }

u8 PPU::getMode()
{
    return ctx.mem().readMem(STAT_ADDR) & 0b11;
}

void PPU::setMode(u8 mode)
{
    // Reset last 2 bits and set new bits
    ctx.mem().writeMem(STAT_ADDR, (ctx.mem().readMem(STAT_ADDR) & 0b11111100) + mode);
}
