#include "../inc/window.hpp"
#include <stdexcept>

void Window::init() {
    window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE);
    if (!window) {
        throw std::runtime_error("Error creating SDL Window");
    }
}

void Window::destroy() {
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

SDL_Window* Window::getWindow() {
    return window;
}

Window::~Window() {
    destroy();
}

int Window::getWidth() {
    int width = 0;
    SDL_GetWindowSizeInPixels(window, &width, nullptr);
    return width;
}

int Window::getHeight() {
    int height = 0;
    SDL_GetWindowSizeInPixels(window, nullptr, &height);
    return height;
}
