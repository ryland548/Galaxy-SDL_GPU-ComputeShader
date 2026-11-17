#include "../inc/camera.hpp"

glm::mat4 Camera::matrix(int w, int h) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(position, position + orientation, up);
    projection = glm::infinitePerspective(glm::radians(fov), static_cast<float>(w) / static_cast<float>(h), nearPlane);

    return projection * view;
}

void Camera::inputs(int w, int h) {
    const bool* keyState = SDL_GetKeyboardState(nullptr);
    if (keyState[SDL_SCANCODE_W]) {
        position += speed * orientation;
    }
    if (keyState[SDL_SCANCODE_A]) {
        position += speed * -glm::normalize(glm::cross(orientation, up));
    }
    if (keyState[SDL_SCANCODE_S]) {
        position += speed * -orientation;
    }
    if (keyState[SDL_SCANCODE_D]) {
        position += speed * glm::normalize(glm::cross(orientation, up));
    }

    float mouseX = 0.0f;
    float mouseY = 0.0f;
    SDL_GetRelativeMouseState(&mouseX, &mouseY);

    float rotX = sensitivity * mouseY;
    float rotY = sensitivity * mouseX;

    glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));
    if (!((glm::angle(newOrientation, up) <= glm::radians(5.0f)) || (glm::angle(newOrientation, -up) <= glm::radians(5.0f)))) {
        orientation = newOrientation;
    }
    orientation = glm::rotate(orientation, glm::radians(-rotY), up);
}

glm::vec3 Camera::getCamRight() {
    return glm::normalize(glm::cross(orientation, up));
}

glm::vec3 Camera::getCamUp() {
    glm::vec3 camRight = glm::normalize(glm::cross(orientation, up));
    return glm::normalize(glm::cross(camRight, orientation));
}
