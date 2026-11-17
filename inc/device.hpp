#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include "context.hpp"

class Device {
public:
    void init(Context& context, SDL_Window* window);
    void destroy(Context& context);
    SDL_GPUDevice* getDevice();
private:
    SDL_GPUDevice* device = nullptr;
};
