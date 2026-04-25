#include <PPU.h>
#include <Context.h>

#define PPU_DEBUG false

PPU::PPU(Context &ctx) : ctx(ctx)
{
    init();
}

PPU::~PPU()
{
}

void PPU::init()
{
    cycles = 0;
    mode = 2;
}

void PPU::run()
{
    // Horizontal blank
    switch (mode)
    {
    // OAM scan
    case 2:
    {
        if (cycles >= 80)
        {
            cycles -= 80;
            mode = 3;
        }
        break;
    }
    // Drawing pixels
    case 3:
    {
        if (cycles >= 172)
        {
            cycles -= 172;
            mode = 0;
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
                mode = 1;
            }
            else
            {
                mode = 2;
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
                mode = 2;
                setLY(0);
            }
        }
        break;
    }
    default:
    {
        std::cerr << std::format("Unknown PPU mode {}\n", mode);
        ctx.setRunning(false);
    }
    }
    cycles++;

#if PPU_DEBUG
    std::cout << std::format("Cycle {}, mode {}, ly {}\n", cycles, mode, getLY());
#endif
}

u8 PPU::getLY()
{
    return ctx.mem().at(LY_ADDR);
}

void PPU::setLY(u8 ly)
{
    ctx.mem().at(LY_ADDR) = ly;
}