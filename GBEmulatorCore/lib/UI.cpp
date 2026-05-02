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
    font = TTF_OpenFont("NotoSansMono-Medium.ttf", 24);
}

void UI::handle()
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        if (evt.type == SDL_EVENT_QUIT)
        {
            ctx.setRunning(false);
        }
    }
}

void UI::update()
{
    if (mainWindow != nullptr)
    {
        int mainSurfaceWidth = UI::SCALE * (16 * UI::TILE_SIZE);
        int mainSurfaceHeight = UI::SCALE * (24 * UI::TILE_SIZE);
        mainSurface = SDL_CreateSurface(mainSurfaceWidth, mainSurfaceHeight, SDL_PIXELFORMAT_RGBA8888);
        updateMainWindow();
    }
    if (debugWindow != nullptr)
    {
        int debugSurfaceWidth = UI::SCALE * (16 * (UI::TILE_SIZE + UI::BLOCK_BLANK));
        // 3*4 for blank between blocks
        int debugSurfaceHeight = 50 + UI::SCALE * (24 * (UI::TILE_SIZE + UI::BLOCK_BLANK) + 3 * UI::BLOCK_BLANK);
        debugSurface = SDL_CreateSurface(debugSurfaceWidth, debugSurfaceHeight, SDL_PIXELFORMAT_RGBA8888);
        updateDebugWindow();
    }
}

void UI::updateMainWindow()
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(getMainRenderer(), mainSurface);
    SDL_RenderClear(getMainRenderer());
    SDL_RenderTexture(getMainRenderer(), texture, nullptr, nullptr);
    SDL_RenderPresent(getMainRenderer());
}

void UI::updateDebugWindow()
{
    SDL_Rect rect;
    for (int tileX = 0; tileX < 16; tileX++)
    {
        for (int tileY = 0; tileY < 24; tileY++)
        {
            int block = tileY / 8;
            ctx.ppu().createTile(UI::SCALE * (tileX * (UI::TILE_SIZE + UI::BLOCK_BLANK)),
                                 50 + UI::SCALE * (tileY * (UI::TILE_SIZE + UI::BLOCK_BLANK) + block * UI::BLOCK_BLANK),
                                 tileY * 16 + tileX,
                                 debugSurface);
        }
    }
    displayText(std::to_string(fps).c_str(), debugSurface, 0, 0, 100, 100);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(getDebugRenderer(), debugSurface);
    SDL_RenderClear(getDebugRenderer());
    SDL_RenderTexture(getDebugRenderer(), texture, nullptr, nullptr);
    SDL_RenderPresent(getDebugRenderer());
}

void UI::destroy()
{
    if (mainWindow != nullptr)
        SDL_DestroyWindow(mainWindow);
    if (debugWindow != nullptr)
        SDL_DestroyWindow(debugWindow);
}
void UI::displayText(const char *text, SDL_Surface *parentWindow, int x, int y, int w, int h)
{
    SDL_Rect position = {x, y, w, h};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, std::to_string(fps).c_str(), 0, {255, 255, 255});
    SDL_BlitSurface(textSurface, &position, parentWindow, nullptr);
}