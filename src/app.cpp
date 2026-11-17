#include "../inc/app.hpp"
#include <stdexcept>
#include <iostream>

void App::run() {
    init();
    loop();
    destroy();
}

void App::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("Error initializing SDL3");
    }
    window.init();
    device.init(context, window.getWindow());

    Shader programShader;
    programShader.init(context, "shader/render/vertex.vert", "shader/render/fragment.frag");
    pipeline.init(context, programShader, window.getWindow());
    programShader.destroy(context);

    renderer.init(context, window.getWindow());
    isRunning = true;

    galaxyBuffer.init(context, 100000, sizeof(Particle));
    compute.init(context, "shader/compute/galaxy.comp");
}

void App::loop() {
    while (isRunning) {
        input();
        update();
        render();
    }
}

void App::input() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        }
        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.key == SDLK_ESCAPE) {
                isRunning = false;
            }
        }
    }
    // camera.inputs(window.getWidth(), window.getHeight());
}

void App::update() {

}

void App::render() {
    int width = window.getWidth();
    int height = window.getHeight();
    if (width > 0 && height > 0) {
        glm::mat4 camMatrix = camera.matrix(width, height);
        PushConstants pushConstant;
        pushConstant.camMatrix = camMatrix;
        pushConstant.camRight = camera.getCamRight();
        pushConstant.camUp = camera.getCamUp();
        renderer.render(context, window.getWindow(), galaxyBuffer, compute, pushConstant);
    }
}

void App::destroy() {
    if (context.device) {
        SDL_WaitForGPUIdle(context.device);
        compute.destroy(context);
        galaxyBuffer.destroy(context);
    }
    renderer.destroy(context);
    pipeline.destroy(context);
    device.destroy(context);
    window.destroy();

    SDL_Quit();
}
