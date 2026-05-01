#include <PPU.h>
#include <Context.h>

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
    setLY(0);
    setMode(2);
}

void PPU::tick()
{
    cycles++;
    u8 mode = getMode();
    // Horizontal blank
    switch (mode)
    {
    // OAM scan
    case 2:
    {
        if (cycles >= 80)
        {
            cycles -= 80;
            setMode(3);
        }
        break;
    }
    // Drawing pixels
    case 3:
    {
        if (cycles >= 172)
        {
            cycles -= 172;
            setMode(0);
        }
        break;
    }
    case 0:
    {
        if (cycles >= 204)
        {
            cycles -= 204;
            setLY(getLY() + 1);
            if (getLY() > 143)
            {
                setMode(1);
            }
            else
            {
                setMode(2);
            }
        }
        break;
    }
    // Vertical blank
    case 1:
    {
        if (cycles >= 456)
        {
            cycles -= 456;
            setLY(getLY() + 1);
            if (getLY() > 153)
            {
                setMode(2);
                setLY(0);
            }
        }
        break;
    }
    default:
    {
        std::cerr << std::format("Unknown PPU mode {}\n", getMode());
        ctx.setRunning(false);
    }
    }
#if PPU_DEBUG
    std::cout << std::format("Cycle {}, mode {}, ly {}\n", cycles, getMode(), getLY());
#endif
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
            u8 color1 = (colorData1 & (1 << bit)) << 1;
            u8 color2 = colorData2 & (1 << bit);

            rect.x = x + (scale * (7 - bit));
            rect.y = y + (scale * (i / 2));
            rect.w = scale;
            rect.h = scale;
            SDL_FillSurfaceRect(surface, &rect, colors[color1 | color2]);
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

u8 PPU::getMode()
{
    return ctx.mem().readMem(STAT_ADDR) & 0b11;
}

void PPU::setMode(u8 mode)
{
    // Reset last 2 bits and set new bits
    ctx.mem().writeMem(STAT_ADDR, (ctx.mem().readMem(STAT_ADDR) & 0b11111100) + mode);
}