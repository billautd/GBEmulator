#include <PPU.h>
#include <Context.h>
#include <Interrupts.h>

#define PPU_DEBUG false

bool oamScanDone = false;
bool drawDone = false;

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
        oamScanDone = false;
        oamScan();
        break;
    case PPU_MODES::DRAWING_PIXELS:
        drawDone = false;
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
    ZoneScoped("HBLANK");
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
    ZoneScoped("VBLANK");
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
    ZoneScoped("OAMSCAN");

    for (int i = 0; i < 40; i++)
    {
        if (oamScanDone)
        {
            break;
        }
        u8 yPos = ctx.mem().readMem(0xFE00 + i * 4);
        u8 xPos = ctx.mem().readMem(0xFE01 + i * 4);
        u8 tileIndex = ctx.mem().readMem(0xFE02 + i * 4);
        u8 flags = ctx.mem().readMem(0xFE03 + i * 4);
        if (yPos == getLY())
        {
            oamScanResult[i] = Sprite{xPos, yPos, tileIndex, flags};
        }
    }
    oamScanDone = true;

    if (lineTicks > 80)
    {
        setMode(PPU_MODES::DRAWING_PIXELS);
    }
}

void PPU::drawPixels()
{
    ZoneScoped("DRAW");
    for (int i = 0; i < 40; i++)
    {
        if (drawDone)
        {
            break;
        }
        Sprite sprite = oamScanResult[i];
        if (sprite.y == getLY())
            createTile(sprite.x - 8, sprite.y - 16, sprite.tileIndex, ctx.ui().getMainSurface());
    }
    drawDone = true;
    if (lineTicks > 172)
    {
        setMode(PPU_MODES::HBLANK);
    }
}

void PPU::createTile(int x, int y, int tileIndex, SDL_Surface *surface)
{
    ZoneScoped("CREATETILE");
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
            ZoneScoped("FILLRECT");
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
