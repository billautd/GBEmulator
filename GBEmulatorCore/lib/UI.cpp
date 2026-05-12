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

    // Init main window/surface/texture
    initMainWindow();
    // Init debug window/surface/texture
#if UI_DEBUG
    initDebugWindow();
#endif

    // Init fonts
    TTF_Init();
    font = TTF_OpenFont("NotoSansMono-Medium.ttf", 24);
}

void UI::initMainWindow()
{
    SDL_CreateWindowAndRenderer("GBEmulator", 600, 800, 0, &mainWindow, &mainRenderer);
    SDL_SetWindowPosition(mainWindow, 400, 400);
    int mainSurfaceWidth = UI::SCALE * (16 * UI::TILE_SIZE);
    int mainSurfaceHeight = UI::SCALE * (24 * UI::TILE_SIZE);
    mainSurface = SDL_CreateSurface(mainSurfaceWidth, mainSurfaceHeight, SDL_PIXELFORMAT_RGBA8888);
    mainTexture = SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
                                    mainSurfaceWidth, mainSurfaceHeight);
}

void UI::initDebugWindow()
{
    SDL_CreateWindowAndRenderer("GBEmulator_DEBUG", 600, 800, 0, &debugWindow, &debugRenderer);
    SDL_SetWindowPosition(debugWindow, 1200, 400);
    int debugSurfaceWidth = UI::SCALE * (16 * (UI::TILE_SIZE + UI::BLOCK_BLANK));
    // 3*4 for blank between blocks
    int debugSurfaceHeight = 50 + UI::SCALE * (24 * (UI::TILE_SIZE + UI::BLOCK_BLANK) + 3 * UI::BLOCK_BLANK);
    debugSurface = SDL_CreateSurface(debugSurfaceWidth, debugSurfaceHeight, SDL_PIXELFORMAT_RGBA8888);
    debugTexture = SDL_CreateTexture(debugRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
                                     debugSurfaceWidth, debugSurfaceHeight);
}

void UI::handle()
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        if (evt.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED || evt.type == SDL_EVENT_QUIT)
        {
            std::cout << "Handle UI exit" << std::endl;
            ctx.setRunning(false);
        }
    }
}

void UI::update()
{
    // Update main window
    updateMainWindow();

// Update debug window
#if UI_DEBUG
    updateDebugWindow();
#endif
}

void UI::updateMainWindow()
{
    SDL_UpdateTexture(mainTexture, nullptr, mainSurface->pixels, mainSurface->pitch);
    SDL_RenderClear(getMainRenderer());
    SDL_RenderTexture(getMainRenderer(), mainTexture, nullptr, nullptr);
    SDL_RenderPresent(getMainRenderer());
    SDL_ClearSurface(mainSurface, 0, 0, 0, 0);
}

void UI::updateDebugWindow()
{
    SDL_ClearSurface(debugSurface, 0, 0, 0, 0);
    SDL_ClearSurface(fpsTextSurface, 0, 0, 0, 0);

    // SDL_Rect rect;
    for (int tileX = 0; tileX < 16; tileX++)
    {
        for (int tileY = 0; tileY < 24; tileY++)
        {
            int block = tileY / 8;
            int tileIndex = tileY * 16 + tileX;
            // 8 pixels, each 16 bytes
            for (int i = 0; i < 16; i += 2)
            {
                int offset = tileIndex * 16;
                u8 colorData1 = ctx.mem().readMem(0x8000 + offset + i);
                u8 colorData2 = ctx.mem().readMem(0x8001 + offset + i);
                for (int bit = 7; bit >= 0; bit--)
                {
                    u8 color1 = (colorData1 >> bit) & 1;
                    u8 color2 = (colorData2 >> bit) & 1;

                    int x = tileX * (UI::TILE_SIZE + UI::BLOCK_BLANK) + 7 - bit;
                    int y = 10 + tileY * (UI::TILE_SIZE + UI::BLOCK_BLANK) + block * UI::BLOCK_BLANK + i / 2;
                    u8 color = (color1 << 1) | color2;

                    ctx.ppu().createPixel(x, y, color, debugSurface);
                }
            }
        }
    }
    displayText(std::to_string(fps).c_str(), debugSurface, fpsTextSurface, {255, 255, 255}, 0, 0, 100, 100);
    SDL_UpdateTexture(debugTexture, nullptr, debugSurface->pixels, debugSurface->pitch);
    SDL_RenderClear(getDebugRenderer());
    SDL_RenderTexture(getDebugRenderer(), debugTexture, nullptr, nullptr);
    SDL_RenderPresent(getDebugRenderer());
}

void UI::destroy()
{
    if (mainWindow != nullptr)
        SDL_DestroyWindow(mainWindow);
    if (debugWindow != nullptr)
        SDL_DestroyWindow(debugWindow);
}

void UI::displayText(const char *text, SDL_Surface *parentSurface, SDL_Surface *textSurface, SDL_Color color, int x, int y, int w, int h)
{
    SDL_Rect position = {x, y, w, h};
    fpsTextSurface = TTF_RenderText_Blended(font, text, 0, color);
    SDL_BlitSurface(fpsTextSurface, &position, debugSurface, nullptr);
}