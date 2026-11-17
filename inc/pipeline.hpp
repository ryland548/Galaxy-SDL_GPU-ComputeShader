#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include "context.hpp"
#include "shader.hpp"

class Pipeline {
public:
    void init(Context& context, Shader& shader, SDL_Window* window);
    void destroy(Context& context);
    SDL_GPUGraphicsPipeline* getPipeline();
private:
    SDL_GPUGraphicsPipeline* pipeline = nullptr;
};
