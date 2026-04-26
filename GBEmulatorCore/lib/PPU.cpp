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

void PPU::run(u64 tCycles)
{
    cycles += tCycles;
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

const static u32 colors[4] = {0xFFFFFFFF, 0xAAAAAAFF, 0x555555FF, 0x000000FF};
void PPU::displayTileMap()
{
    int scale = 5;
    SDL_Surface *surface = SDL_CreateSurface(800, 600, SDL_PIXELFORMAT_RGBA8888);
    SDL_Rect rect;
    for (int tile = 0; tile < 16 * 24; tile++)
    {
        for (int i = 0; i < 16; i += 2)
        {
            u8 colorData1 = ctx.mem().at((0x8000 + tile * 16) + i);
            u8 colorData2 = ctx.mem().at((0x8000 + tile * 16) + i);
            for (int bit = 7; bit >= 0; bit--)
            {
                u8 color1 = (colorData1 & (1 << bit)) << 1;
                u8 color2 = colorData2 & (1 << bit);

                rect.x = scale * ((7 - bit) + 8 * (tile % 32));
                rect.y = scale * ((i / 2) + 8 * (tile / 32));
                rect.w = scale;
                rect.h = scale;
                SDL_FillSurfaceRect(surface, &rect, colors[color1 | color2]);
            }
        }
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ctx.getRenderer(), surface);
    SDL_RenderTexture(ctx.getRenderer(), texture, nullptr, nullptr);
    SDL_RenderPresent(ctx.getRenderer());
}

u8 PPU::getLY()
{
    return ctx.mem().at(LY_ADDR);
}

void PPU::setLY(u8 ly)
{
    ctx.mem().at(LY_ADDR) = ly;
}