#pragma once
#include <glm/glm.hpp>

struct Particle {
    alignas(16) glm::vec3 position;
    alignas(16) glm::vec4 color;
    alignas(16) float size;
};


