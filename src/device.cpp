#include "../inc/device.hpp"
#include <stdexcept>

void Device::init(Context& context, SDL_Window* window) {
    #ifdef DEBUG
        SDL_SetLogPriorities(SDL_LOG_PRIORITY_TRACE);
    #else
        SDL_SetLogPriorities(SDL_LOG_PRIORITY_WARN);
    #endif

    SDL_GPUShaderFormat formats = SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL;
    device = SDL_CreateGPUDevice(formats, false, nullptr);
    if (!device) {
        throw std::runtime_error("Error creating SDL device");
    }
    context.device = device;
    context.driver = SDL_GetGPUDeviceDriver(device);

    if (!SDL_ClaimWindowForGPUDevice(device, window)) {
        destroy(context);
        throw std::runtime_error("Failed to claim SDL window");
    }
}

void Device::destroy(Context& context) {
    if (device) {
        SDL_DestroyGPUDevice(device);
        device = nullptr;
        context.device = nullptr;
        context.driver = nullptr;
    }
}

SDL_GPUDevice* Device::getDevice() {
    return device;
}
