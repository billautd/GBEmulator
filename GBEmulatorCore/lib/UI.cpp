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

    int surfaceWidth = scale * (16 * tileSize);
    // 3*4 for blank between blocks
    int surfaceHeight = 50 + scale * (24 * tileSize + 3 * blockBlank);

    SDL_Surface *surface = SDL_CreateSurface(surfaceWidth, surfaceHeight, SDL_PIXELFORMAT_RGBA8888);
    SDL_Rect rect;
    for (int tileX = 0; tileX < 16; tileX++)
    {
        for (int tileY = 0; tileY < 24; tileY++)
        {
            int block = tileY / 8;
            ctx.ppu().createTile(scale * (tileX * tileSize),
                                 50 + scale * (tileY * tileSize + block * blockBlank),
                                 tileY * 16 + tileX,
                                 scale,
                                 surface);
        }
    }
    displayText(std::to_string(fps).c_str(), surface, 0, 0, 100, 100);
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
void UI::displayText(const char *text, SDL_Surface *parentWindow, int x, int y, int w, int h)
{
    SDL_Rect position = {x, y, w, h};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, std::to_string(fps).c_str(), 0, {255, 255, 255});
    SDL_BlitSurface(textSurface, &position, parentWindow, nullptr);
}