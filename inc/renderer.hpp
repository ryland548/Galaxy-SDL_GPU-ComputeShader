#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <glm/glm.hpp>
#include "context.hpp"
#include "buffer.hpp"
#include "shader.hpp"
#include "compute.hpp"

class Renderer {
public:
    void init(Context& context, SDL_Window* window);
    void render(Context& context, SDL_Window* window, Buffer& galaxyBuffer, Compute& compute, PushConstants& pushConstant);
    void destroy(Context& context);
private:
    void createDepthTexture(Context& context, uint32_t width, uint32_t height);

    SDL_GPUTexture* depthTexture = nullptr;
    uint32_t depthWidth = 0;
    uint32_t depthHeight = 0;
};
