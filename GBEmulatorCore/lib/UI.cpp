#include <UI.h>
#include <Context.h>
#include <SDL3_ttf/SDL_ttf.h>

#define UI_DEBUG true

UI::UI(Context &ctx) : ctx(ctx)
{
}
UI::~UI()
{
}

void UI::init()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("GBEmulator", 600, 800, 0, &mainWindow, &mainRenderer);
    SDL_SetWindowPosition(mainWindow, 400, 400);
#if UI_DEBUG
    SDL_CreateWindowAndRenderer("GBEmulator_DEBUG", 600, 800, 0, &debugWindow, &debugRenderer);
    SDL_SetWindowPosition(debugWindow, 1200, 400);
#endif

    // Init fonts
    TTF_Init();
}

void UI::handle()
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        if (evt.type == SDL_EVENT_QUIT)
        {
            ctx.destroy();
        }
    }
}

int i = 0;
void UI::update()
{
    if (debugWindow != nullptr)
    {
        updateDebugWindow();
    }
}

void UI::updateDebugWindow()
{
    // 0x8000 to 0x9FFF
    int scale = 5;
    int tileSize = 8 + 2;
    int blockBlank = 4;

    SDL_Surface *surface = SDL_CreateSurface(
        scale * (16 * tileSize),
        // 3*4 for blank between blocks
        scale * (24 * tileSize + 3 * blockBlank),
        SDL_PIXELFORMAT_RGBA8888);
    SDL_Rect rect;
    for (int tileX = 0; tileX < 16; tileX++)
    {
        for (int tileY = 0; tileY < 24; tileY++)
        {
            int block = tileY / 8;
            ctx.ppu().createTile(scale * (tileX * tileSize),
                                 scale * (tileY * tileSize + block * blockBlank),
                                 tileY * 16 + tileX,
                                 scale,
                                 surface);
        }
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(getDebugRenderer(), surface);
    SDL_RenderClear(getDebugRenderer());
    SDL_RenderTexture(getDebugRenderer(), texture, nullptr, nullptr);
    SDL_RenderPresent(getDebugRenderer());
}

void UI::destroy()
{
    SDL_DestroyWindow(mainWindow);
    if (debugWindow != nullptr)
    {
        SDL_DestroyWindow(debugWindow);
    }
}