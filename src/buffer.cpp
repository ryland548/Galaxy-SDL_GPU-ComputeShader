#include "../inc/buffer.hpp"
#include <stdexcept>

void Buffer::init(Context& context, uint32_t elementCount, uint32_t elementStride) {
    count = elementCount;
    size = count * elementStride;

    SDL_GPUBufferUsageFlags flags =
        SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_READ |
        SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_WRITE |
        SDL_GPU_BUFFERUSAGE_GRAPHICS_STORAGE_READ;

    SDL_GPUBufferCreateInfo bufferInfo{};
    bufferInfo.usage = flags;
    bufferInfo.size = size;

    buffer = SDL_CreateGPUBuffer(context.device, &bufferInfo);
    if (!buffer) {
        throw std::runtime_error("Failed to create GPU buffer");
    }
}

void Buffer::destroy(Context& context) {
    if (buffer) {
        SDL_ReleaseGPUBuffer(context.device, buffer);
        buffer = nullptr;
        count = 0;
        size = 0;
    }
}

uint32_t Buffer::getCount() {
    return count;
}

SDL_GPUBuffer* Buffer::getBuffer() {
    return buffer;
}
