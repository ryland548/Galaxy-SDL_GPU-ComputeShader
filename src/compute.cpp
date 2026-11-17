#include "../inc/compute.hpp"

void Compute::init(Context& context, std::string path) {
    SDL_GPUShaderFormat format;
    std::string extension = "";
    std::string entrypoint = "";

    if (strcmp(context.driver, "vulkan") == 0) {
        format = SDL_GPU_SHADERFORMAT_SPIRV;
        extension = ".spv";
        entrypoint = "main";
    } else if (strcmp(context.driver, "direct3d12") == 0) {
        format = SDL_GPU_SHADERFORMAT_DXIL;
        extension = ".dxil";
        entrypoint = "main";
    } else if (strcmp(context.driver, "metal") == 0) {
        format = SDL_GPU_SHADERFORMAT_MSL;
        extension = ".msl";
        entrypoint = "main0";
    } else {
        throw std::runtime_error("Unsupported GPU backend");
    }

    auto code = loadShader(path + extension);
    if (format == SDL_GPU_SHADERFORMAT_MSL) {
        code.push_back('\0');
    }

    SDL_GPUComputePipelineCreateInfo info{};
    info.code = code.data();
    info.code_size = code.size();
    info.entrypoint = entrypoint.c_str();
    info.format = format;
    info.num_readwrite_storage_buffers = 1;
    info.num_uniform_buffers = 1;
    info.threadcount_x = 256;
    info.threadcount_y = 1;
    info.threadcount_z = 1;

    pipeline = SDL_CreateGPUComputePipeline(context.device, &info);
    if (!pipeline) {
        throw std::runtime_error("Error creating compute pipeline");
    }
}

void Compute::destroy(Context& context) {
    if (pipeline) {
        SDL_ReleaseGPUComputePipeline(context.device, pipeline);
        pipeline = nullptr;
    }
}

SDL_GPUComputePipeline* Compute::getPipeline() {
    return pipeline;
}
