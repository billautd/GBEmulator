#pragma once

#include <Common.h>

class Context;
class UI
{
private:
    Context &ctx;

    float fps;
    TTF_Font *font;

    // Main window
    SDL_Window *mainWindow = nullptr;
    SDL_Renderer *mainRenderer = nullptr;
    SDL_Surface *mainSurface = nullptr;
    SDL_Texture *mainTexture = nullptr;

    // Debug window
    SDL_Window *debugWindow = nullptr;
    SDL_Renderer *debugRenderer = nullptr;
    SDL_Surface *debugSurface = nullptr;
    SDL_Surface *fpsTextSurface = nullptr;
    SDL_Texture *debugTexture = nullptr;

    void displayText(const char *text, SDL_Surface *parentWindow, SDL_Surface *textSurface, SDL_Color color, int x, int y, int w, int h);

    void initMainWindow();
    void initDebugWindow();

    void updateMainWindow();
    void updateDebugWindow();

    const static int TILE_SIZE = 8;
    const static int BLOCK_BLANK = 2;

public:
    UI(Context &context);
    ~UI();

    const static int SCALE = 5;

    void init();
    void handle();
    void update();
    void destroy();

    void setFPS(float fps) { this->fps = fps; }

    SDL_Window *getMainWindow() { return mainWindow; }
    SDL_Renderer *getMainRenderer() { return mainRenderer; }
    SDL_Surface *getMainSurface() { return mainSurface; }

    SDL_Window *getDebugWindow() { return debugWindow; }
    SDL_Renderer *getDebugRenderer() { return debugRenderer; }
    SDL_Surface *getDebugSurface() { return debugSurface; }
};