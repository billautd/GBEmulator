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
    setMode(PPUModes::OAM_SCAN);
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
        std::cerr << std::format("Unknown PPU mode {}\n", (int)getMode());
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
    /** Do one OAM scan every other dot, to space out within 80 dots
     * Line tick 0 == 0xFE00-0xFE03
     * Line tick 2 == 0xFE04 - 0xFE07
     *...
     * Line tick 78 == 0xFE9C - 0xFE9F
     * Line tick n = (0xFE00 + lineTick * 2) - (0xFE03 + lineTick * 2)
     * if (lineTicks % 2 == 0)
     * {
     *     u16 addr = 0xFE00 + (lineTicks / 2) * 4;
     *     u8 yPos = ctx.mem().readMem(addr);
     *     if (getLY() >= ((int)yPos - 16) && getLY() < ((int)yPos - 8))
     *     {
     *         u8 xPos = ctx.mem().readMem(addr + 1);
     *         u8 tileIndex = ctx.mem().readMem(addr + 2);
     *         u8 flags = ctx.mem().readMem(addr + 3);
     *         oamScanResult.emplace_back(Sprite{xPos, yPos, tileIndex, flags});
     *     }
     */
    if (lineTicks >= 80)
    {
        setMode(PPUModes::DRAWING_PIXELS);
    }
}

void PPU::drawPixels()
{
    if (lineTicks >= 160 + 80)
    {
        setMode(PPUModes::HBLANK);
    }
}

void PPU::createPixel(int x, int y, u8 color, SDL_Surface *surface)
{
    if (surface == nullptr)
    {
        std::cerr << "Surface is NULL" << std::endl;
        return;
    }
    SDL_Rect rect;
    rect.x = UI::SCALE * x;
    rect.y = UI::SCALE * y;
    rect.w = UI::SCALE;
    rect.h = UI::SCALE;
    SDL_FillSurfaceRect(surface, &rect, colors[color]);
}

u8 PPU::getLY()
{
    return ctx.mem().readMem(LY);
}

void PPU::setLY(u8 ly)
{
    ctx.mem().writeMem(LY, ly);
}

void PPU::incrementLY()
{
    setLY(getLY() + 1);

    if (getLY() == getLYC())
    {
        ctx.mem().writeMem(STAT, Common::setBit(ctx.mem().readMem(STAT), 2));
        if (getLCDStatus(LCDStatuses::LYC_INT))
            ctx.cpu().getInterrupts().requestInterrupt(InterruptType::INT_LCD);
    }
    else
        ctx.mem().writeMem(STAT, Common::resetBit(ctx.mem().readMem(STAT), 2));
}

u8 PPU::getLYC()
{
    return ctx.mem().readMem(LYC);
}

bool PPU::getLCDStatus(LCDStatuses status)
{
    return Common::getBit(ctx.mem().readMem(STAT), status);
}

bool PPU::getLCDControl(LCDControls control)
{
    return Common::getBit(ctx.mem().readMem(LCDC), control);
}

u8 PPU::getWX()
{
    return ctx.mem().readMem(WX);
}

u8 PPU::getWY()
{
    return ctx.mem().readMem(WY);
}

u8 PPU::getMode()
{
    return ctx.mem().readMem(STAT) & 0b11;
}

void PPU::setMode(u8 mode)
{
    // Reset last 2 bits and set new bits
    u8 previousMode = getMode();
    ctx.mem().writeMem(STAT, (ctx.mem().readMem(STAT) & 0b11111100) + mode);

    // Request interrupt if mode changed and interrupt bit enabled
    bool modeChanged = previousMode != mode;
    if (modeChanged)
    {
        if ((mode == PPUModes::HBLANK && getLCDStatus(LCDStatuses::MODE_0)) ||
            (mode == PPUModes::VBLANK && getLCDStatus(LCDStatuses::MODE_1)) ||
            (mode == PPUModes::OAM_SCAN && getLCDStatus(LCDStatuses::MODE_2)))
            ctx.cpu().getInterrupts().requestInterrupt(InterruptType::INT_LCD);
    }
}

void PPU::vram_write(u16 address, u8 value)
{
    ctx.mem().simpleWrite(address, value);
}

u8 &PPU::vram_read(u16 address)
{
    return ctx.mem().simpleRead(address);
}

void PPU::oam_write(u16 address, u8 value)
{
    if (ctx.dma().isRunning())
        return;
    ctx.mem().simpleWrite(address, value);
}

u8 &PPU::oam_read(u16 address)
{
    return ctx.mem().simpleRead(address);
}

void PPU::lcd_write(u16 address, u8 value)
{
    ctx.mem().simpleWrite(address, value);
}

u8 &PPU::lcd_read(u16 address)
{
    return ctx.mem().simpleRead(address);
}