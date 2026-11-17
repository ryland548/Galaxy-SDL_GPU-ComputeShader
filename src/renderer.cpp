#include "../inc/renderer.hpp"
#include <stdexcept>

void Renderer::init(Context& context, SDL_Window* window) {
    int width = 0;
    int height = 0;
    SDL_GetWindowSizeInPixels(window, &width, &height);

    if (width > 0 && height > 0 ) {
        createDepthTexture(context, static_cast<uint32_t>(width), static_cast<uint32_t>(height));
    }
}

void Renderer::createDepthTexture(Context& context, uint32_t width, uint32_t height) {
    if (depthTexture) {
        SDL_ReleaseGPUTexture(context.device, depthTexture);
        depthTexture = nullptr;
    }

    SDL_GPUTextureCreateInfo depthInfo{};
    depthInfo.type = SDL_GPU_TEXTURETYPE_2D;
    depthInfo.format = SDL_GPU_TEXTUREFORMAT_D32_FLOAT;
    depthInfo.usage = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET;
    depthInfo.width = width;
    depthInfo.height = height;
    depthInfo.layer_count_or_depth = 1;
    depthInfo.num_levels = 1;

    depthTexture = SDL_CreateGPUTexture(context.device, &depthInfo);
    if (!depthTexture) {
        throw std::runtime_error("Failed to create depth texture");
    }

    depthWidth = width;
    depthHeight = height;
}

void Renderer::render(Context& context, SDL_Window* window, Buffer& galaxyBuffer, Compute& compute, PushConstants& pushConstant) {
    SDL_GPUCommandBuffer* command = SDL_AcquireGPUCommandBuffer(context.device);
    if (!command) {
        return;
    }

    SDL_GPUStorageBufferReadWriteBinding binding{};
    binding.buffer = galaxyBuffer.getBuffer();
    binding.cycle = false;

    SDL_GPUComputePass* computePass = SDL_BeginGPUComputePass(command, nullptr, 0, &binding, 1);
    SDL_BindGPUComputePipeline(computePass, compute.getPipeline());

    SimulationUniform simUniform{};
    simUniform.count = galaxyBuffer.getCount();
    simUniform.time = static_cast<float>(SDL_GetTicks()) / 1000.0f;
    SDL_PushGPUComputeUniformData(command, 0, &simUniform, sizeof(SimulationUniform));

    uint32_t groupCountX = (galaxyBuffer.getCount() + 255) / 256;
    SDL_DispatchGPUCompute(computePass, groupCountX, 1, 1);

    SDL_EndGPUComputePass(computePass);

    SDL_GPUTexture* swapchainTexture = nullptr;
    uint32_t width = 0;
    uint32_t height = 0;

    if (SDL_WaitAndAcquireGPUSwapchainTexture(command, window, &swapchainTexture, &width, &height)) {
        if (swapchainTexture && width > 0 && height > 0) {
            if (!depthTexture || depthWidth != width || depthHeight != height) {
                createDepthTexture(context, width, height);
            }

            SDL_GPUColorTargetInfo colorTarget{};
            colorTarget.texture = swapchainTexture;
            colorTarget.clear_color = {0.0f, 0.0f, 0.0f, 1.0f};
            colorTarget.load_op = SDL_GPU_LOADOP_CLEAR;
            colorTarget.store_op = SDL_GPU_STOREOP_STORE;

            SDL_GPUDepthStencilTargetInfo depthTarget{};
            depthTarget.texture = depthTexture;
            depthTarget.clear_depth = 1.0f;
            depthTarget.load_op = SDL_GPU_LOADOP_CLEAR;
            depthTarget.store_op = SDL_GPU_STOREOP_DONT_CARE;

            SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(command, &colorTarget, 1, &depthTarget);

            SDL_BindGPUGraphicsPipeline(renderPass, context.particlePipeline);

            SDL_GPUBuffer* rawBuffer = galaxyBuffer.getBuffer();
            SDL_BindGPUVertexStorageBuffers(renderPass, 0, &rawBuffer, 1);

            SDL_PushGPUVertexUniformData(command, 0, &pushConstant, sizeof(PushConstants));
            SDL_DrawGPUPrimitives(renderPass, galaxyBuffer.getCount() * 6, 1, 0, 0);

            SDL_EndGPURenderPass(renderPass);
        }
    }

    SDL_SubmitGPUCommandBuffer(command);
}

void Renderer::destroy(Context& context) {
    if (depthTexture) {
        SDL_ReleaseGPUTexture(context.device, depthTexture);
        depthTexture = nullptr;
    }
}
