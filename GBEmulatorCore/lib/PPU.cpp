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
    PPUModes mode = getMode();
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
        if (getLY() >= YRES)
        {
            setMode(PPUModes::VBLANK);
            ctx.cpu().getInterrupts().requestInterrupt(InterruptType::INT_VBLANK);
            if (getLCDStatus(LCDStatuses::MODE_1))
                ctx.cpu().getInterrupts().requestInterrupt(InterruptType::INT_LCD);
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
    if (lineTicks >= OAM_SCAN_TICKS)
    {
        setMode(PPUModes::DRAWING_PIXELS);
        currentFIFOFetcherState = FIFOFetcherState::TILE;
    }
}

void PPU::drawPixels()
{
    if (fifoDelay > 0)
    {
        fifoDelay--;
    }
    else if (!renderReady)
    {
        switch (currentFIFOFetcherState)
        {
        case FIFOFetcherState::TILE:
        {

            // Get X and Y coordinate relating to where we are in the tilemap
            currentFIFOTileMapX = ((getSCX() + currentFIFOX) & 0xFF) / 8;
            currentFIFOTileMapY = ((getSCY() + getLY()) & 0xFF) / 8;
            currentFIFOTileY = (getSCY() + getLY()) & 7;
            currentFIFOFetcherState = FIFOFetcherState::TILE_LOW;
            // Takes 2 dots
            fifoDelay = 1;
            break;
        }
        case FIFOFetcherState::TILE_LOW:
        {
            // Tile map contains id of tile in tile data (with 0x8000 or 0x8800 addressing)
            u16 tileAddress = 0x8000 + 16 * ctx.mem().readMem(getTileMapBase() + currentFIFOTileMapY * 32 + currentFIFOTileMapX) + 2 * currentFIFOTileY;
            currentFIFOTileLow = ctx.mem().readMem(tileAddress);
            currentFIFOFetcherState = FIFOFetcherState::TILE_HIGH;
            // Takes 2 dots
            fifoDelay = 1;
            break;
        }
        case FIFOFetcherState::TILE_HIGH:
        {
            // Tile map contains id of tile in tile data (with 0x8000 or 0x8800 addressing)
            u16 tileAddress = 0x8000 + 16 * ctx.mem().readMem(getTileMapBase() + currentFIFOTileMapY * 32 + currentFIFOTileMapX) + 2 * currentFIFOTileY + 1;
            currentFIFOTileHigh = ctx.mem().readMem(tileAddress);
            currentFIFOFetcherState = FIFOFetcherState::SLEEP;
            // Takes 2 dots
            fifoDelay = 1;
            break;
        }
        case FIFOFetcherState::SLEEP:
        {
            fifoDelay = 2;
            currentFIFOFetcherState = FIFOFetcherState::PUSH;
            break;
        }
        case FIFOFetcherState::PUSH:
        {
            if (fifo.empty())
            {
                for (int bit = 7; bit >= 0; bit--)
                {
                    u8 color1 = (currentFIFOTileLow >> bit) & 1;
                    u8 color2 = (currentFIFOTileHigh >> bit) & 1;

                    int x = currentFIFOX + 7 - bit;
                    int y = getLY();
                    u8 colorIndex = (color1 << 1) | color2;

                    fifo.push({x, y, colorIndex});
                }
                currentFIFOX += 8;
                renderReady = true;
            }
        }
            currentFIFOFetcherState = FIFOFetcherState::TILE;
            break;
        }
    }
    else
    {
        if (!fifo.empty())
        {
            Pixel pixel = fifo.front();
            fifo.pop();
            drawPixel(pixel, ctx.ui().getMainSurface());
        }
        if (fifo.empty())
        {
            renderReady = false;
        }
    }
    if (currentFIFOX >= XRES)
    {
        clearFIFO();
        currentFIFOX = 0;
        setMode(PPUModes::HBLANK);
        if (getLCDStatus(LCDStatuses::MODE_0))
            ctx.cpu().getInterrupts().requestInterrupt(InterruptType::INT_LCD);
    }
}

u16 PPU::getTileMapBase()
{
    // TODO : Do condition for fetching at 0x9C00
    return 0x9800;
}

void PPU::drawPixel(const Pixel &pixel, SDL_Surface *surface)
{
    if (surface == nullptr)
    {
        std::cerr << "Surface is NULL" << std::endl;
        return;
    }
    SDL_Rect rect;
    rect.x = UI::SCALE * pixel.x;
    rect.y = UI::SCALE * pixel.y;
    rect.w = UI::SCALE;
    rect.h = UI::SCALE;
    // TODO : Only reads BG palette, also check OBP0 and OBP1 for sprites
    SDL_FillSurfaceRect(surface, &rect, colors[(getBGP() >> (pixel.colorIndex * 2)) & 0b11]);
}

u8 PPU::getSCX()
{
    return ctx.mem().readMem(SCX);
}

u8 PPU::getSCY()
{
    return ctx.mem().readMem(SCY);
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
        // Set LY == LYC bit
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

u8 PPU::getBGP()
{
    return ctx.mem().readMem(BGP);
}

bool PPU::getLCDStatus(LCDStatuses status)
{
    return Common::getBit(ctx.mem().readMem(STAT), (int)status);
}

bool PPU::getLCDControl(LCDControls control)
{
    return Common::getBit(ctx.mem().readMem(LCDC), (int)control);
}

u8 PPU::getWX()
{
    return ctx.mem().readMem(WX);
}

u8 PPU::getWY()
{
    return ctx.mem().readMem(WY);
}

bool PPU::isWindowVisible()
{
    return getLCDControl(LCDControls::WINDOW_ENABLE) &&
           getWX() >= 0 && getWX() <= XRES &&
           getWY() >= 0 && getWY() <= YRES;
}

PPUModes PPU::getMode()
{
    return (PPUModes)(ctx.mem().readMem(STAT) & 0b11);
}

void PPU::setMode(PPUModes mode)
{
    // Reset last 2 bits and set new bits
    PPUModes previousMode = getMode();
    ctx.mem().writeMem(STAT, (ctx.mem().readMem(STAT) & 0b11111100) + (int)mode);

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