#include "../inc/shader.hpp"
#include <fstream>
#include <stdexcept>
#include <cstring>

std::vector<Uint8> loadShader(std::string path) {
    std::ifstream file(path.c_str(), std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Failed to open shader. " + path);
    }

    const auto size = file.tellg();
    std::vector<Uint8> data(static_cast<size_t>(size));

    file.seekg(0);
    file.read(reinterpret_cast<char*>(data.data()), size);

    return data;
}

void Shader::init(Context& context, std::string vertexPath, std::string fragmentPath) {
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

    auto vertexCode = loadShader(vertexPath + extension);
    if (format == SDL_GPU_SHADERFORMAT_MSL) {
        vertexCode.push_back('\0');
    }
    auto fragmentCode = loadShader(fragmentPath + extension);
    if (format == SDL_GPU_SHADERFORMAT_MSL) {
        fragmentCode.push_back('\0');
    }

    SDL_GPUShaderCreateInfo vertexInfo{};
    vertexInfo.code = vertexCode.data();
    vertexInfo.code_size = vertexCode.size();
    vertexInfo.entrypoint = entrypoint.c_str();
    vertexInfo.format = format;
    vertexInfo.stage = SDL_GPU_SHADERSTAGE_VERTEX;
    vertexInfo.num_samplers = 0;
    vertexInfo.num_storage_buffers = 1;
    vertexInfo.num_storage_textures = 0;
    vertexInfo.num_uniform_buffers = 1;

    vertexShader = SDL_CreateGPUShader(context.device, &vertexInfo);

    SDL_GPUShaderCreateInfo fragmentInfo{};
    fragmentInfo.code = fragmentCode.data();
    fragmentInfo.code_size = fragmentCode.size();
    fragmentInfo.entrypoint = entrypoint.c_str();
    fragmentInfo.format = format;
    fragmentInfo.stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
    fragmentInfo.num_samplers = 0;
    fragmentInfo.num_storage_buffers = 0;
    fragmentInfo.num_storage_textures = 0;
    fragmentInfo.num_uniform_buffers = 0;

    fragmentShader = SDL_CreateGPUShader(context.device, &fragmentInfo);
}

void Shader::destroy(Context& context) {
    if (vertexShader) {
        SDL_ReleaseGPUShader(context.device, vertexShader);
        vertexShader = nullptr;
    }
    if (fragmentShader) {
        SDL_ReleaseGPUShader(context.device, fragmentShader);
        fragmentShader = nullptr;
    }
}

SDL_GPUShader* Shader::getVertexShader() {
    return vertexShader;
}

SDL_GPUShader* Shader::getFragmentShader() {
    return fragmentShader;
}
