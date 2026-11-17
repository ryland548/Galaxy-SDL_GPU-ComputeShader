#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <string>
#include "context.hpp"
#include "shader.hpp"

struct SimulationUniform {
    uint32_t count;
    float time;
};

class Compute {
public:
    void init(Context& context, std::string path);
    void destroy(Context& context);
    SDL_GPUComputePipeline* getPipeline();
private:
    SDL_GPUComputePipeline* pipeline = nullptr;
};
