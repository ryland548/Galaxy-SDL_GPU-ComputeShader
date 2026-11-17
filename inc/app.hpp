#pragma once
#include "window.hpp"
#include "context.hpp"
#include "device.hpp"
#include "shader.hpp"
#include "pipeline.hpp"
#include "renderer.hpp"
#include "buffer.hpp"
#include "camera.hpp"
#include "particle.hpp"
#include "compute.hpp"

class App {
public:
    void run();
    void init();
    void loop();
    void input();
    void update();
    void render();
    void destroy();
private:
    Device device;
    Pipeline pipeline;
    Renderer renderer;
    Window window;
    Context context;
    SDL_Event event;
    Camera camera;
    Buffer galaxyBuffer;
    Compute compute;
    bool isRunning = true;
};
