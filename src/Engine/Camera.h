#ifndef HYDROGEN_CAMERA_H
#define HYDROGEN_CAMERA_H

#include "include.h"

namespace Engine{
    class Camera {
    private:
    public:
        Camera(){};
        Camera(const glm::vec3 &_cameraPos, const glm::vec3 &_cameraFront, float _fov, float scr_width,
               float scr_height);
        void updateCamera(const glm::vec3& _cameraPos, const glm::vec3& _cameraFront, float _fov, float scr_width, float scr_height);

        glm::mat4 getCameraMatrix();
        glm::vec3 getCameraPos();
    private:
        float fov;
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4 view;
        glm::mat4 projection;
    };
}


#endif //HYDROGEN_CAMERA_H
