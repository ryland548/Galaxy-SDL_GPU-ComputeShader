#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include "context.hpp"

class Buffer {
public:
    void init(Context& context, uint32_t elementCount, uint32_t elementStride);
    void destroy(Context& context);
    SDL_GPUBuffer* getBuffer();
    uint32_t getCount();
private:
    SDL_GPUBuffer* buffer = nullptr;
    uint32_t count;
    uint32_t size;
};
