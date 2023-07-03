#include "Camera.h"

Camera::Camera(const glm::vec3 &_cameraPos, const glm::vec3 &_cameraFront, float fov, float scr_width,
               float scr_height) {
    updateCamera(cameraPos, cameraFront, fov, scr_width, scr_height);
}

void Camera::updateCamera(const glm::vec3 &_cameraPos, const glm::vec3 &_cameraFront, float fov, float scr_width,
                          float scr_height) {
    cameraPos = _cameraPos;
    cameraFront = _cameraFront;

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    projection = glm::perspective(glm::radians(fov), ((float)scr_width / (float)scr_height), 0.1f, 100.0f);
}


glm::mat4 Camera::getCameraMatrix() {
    return projection * view;
}