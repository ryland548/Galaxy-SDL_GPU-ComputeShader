#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "context.hpp"

struct PushConstants {
    glm::mat4 camMatrix;
    alignas(16) glm::vec3 camRight;
    alignas(16) glm::vec3 camUp;
};

std::vector<Uint8> loadShader(std::string path);

class Shader {
public:
    void init(Context& context, std::string vertexPath, std::string fragmentPath);
    void destroy(Context& context);
    SDL_GPUShader* getVertexShader();
    SDL_GPUShader* getFragmentShader();
private:
    SDL_GPUShader* vertexShader = nullptr;
    SDL_GPUShader* fragmentShader = nullptr;
};
