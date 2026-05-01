#pragma once

#include <Common.h>

class Context;
class UI
{
private:
    Context &ctx;

    // Main window
    float mainWindowFps;
    SDL_Window *mainWindow = nullptr;
    SDL_Renderer *mainRenderer;

    // Debug window
    float debugWindowFps;
    SDL_Window *debugWindow = nullptr;
    SDL_Renderer *debugRenderer;

    void updateDebugWindow();

public:
    UI(Context &context);
    ~UI();

    void init();
    void handle();
    void update();
    void destroy();

    SDL_Window *getMainWindow() { return mainWindow; }
    SDL_Renderer *getMainRenderer() { return mainRenderer; }
    void setMainWindowFPS(float fps) { mainWindowFps = fps; }

    SDL_Window *getDebugWindow() { return debugWindow; }
    SDL_Renderer *getDebugRenderer() { return debugRenderer; }
};