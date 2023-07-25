#include "Camera.h"

namespace Engine{
    Camera::Camera(const glm::vec3 &_cameraPos, const glm::vec3 &_cameraFront, float _fov, float scr_width,
                   float scr_height) {
        updateCamera(_cameraPos, _cameraFront, _fov, scr_width, scr_height);
    }

    void Camera::updateCamera(const glm::vec3 &_cameraPos, const glm::vec3 &_cameraFront, float _fov, float scr_width,
                              float scr_height) {
        cameraPos = _cameraPos;
        cameraFront = _cameraFront;
        fov = _fov;

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        projection = glm::perspective(glm::radians(_fov), ((float)scr_width / (float)scr_height), 0.1f, 100.0f);
    }



    glm::mat4 Camera::getCameraMatrix() {
        return projection * view;
    }

    glm::vec3 Camera::getCameraPos() {
        return cameraPos;
    }

    glm::mat4 Camera::getViewMatrix() {
        return view;
    }

}