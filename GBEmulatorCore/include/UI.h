#pragma once

#include <Common.h>

class Context;
class UI
{
private:
    Context &ctx;

    float fps;

    // Main window
    SDL_Window *mainWindow = nullptr;
    SDL_Renderer *mainRenderer;

    // Debug window
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

    void setFPS(float fps) { this->fps = fps; }

    SDL_Window *getMainWindow() { return mainWindow; }
    SDL_Renderer *getMainRenderer() { return mainRenderer; }

    SDL_Window *getDebugWindow() { return debugWindow; }
    SDL_Renderer *getDebugRenderer() { return debugRenderer; }
};