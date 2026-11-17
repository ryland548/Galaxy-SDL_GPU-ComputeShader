#pragma once
#include <SDL3/SDL.h>
#include <string>

class Window {
public:
    ~Window();
    void init();
    void destroy();
    int getWidth();
    int getHeight();
    SDL_Window* getWindow();
private:
    SDL_Window* window = nullptr;
    int width = 800;
    int height = 800;
    std::string title = "Galaxy";
};
