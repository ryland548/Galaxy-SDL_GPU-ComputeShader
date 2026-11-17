#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>

struct Context {
    SDL_GPUDevice* device = nullptr;
    SDL_GPUGraphicsPipeline* particlePipeline;
    const char* driver = nullptr;
};
