#ifndef HYDROGEN_CAMERA_H
#define HYDROGEN_CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
public:
    Camera(const glm::vec3 &_cameraPos, const glm::vec3 &_cameraFront, float fov, float scr_width,
           float scr_height);
    void updateCamera(const glm::vec3& _cameraPos, const glm::vec3& _cameraFront, float fov, float scr_width, float scr_height);
    glm::mat4 getCameraMatrix();
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view;
    glm::mat4 projection;
};


#endif //HYDROGEN_CAMERA_H
