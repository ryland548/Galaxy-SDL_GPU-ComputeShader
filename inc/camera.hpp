#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera {
public:
    void inputs(int w, int h);
    glm::mat4 matrix(int w, int h);
    glm::vec3 getCamRight();
    glm::vec3 getCamUp();
    glm::vec3 position = glm::vec3(0.111575f, -1.51538, 135.57f);
private:
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float speed = 0.1f;
    float sensitivity = 0.1f;
    float fov = 60.0f;
    float nearPlane = 0.01f;
};
