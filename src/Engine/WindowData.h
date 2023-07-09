#ifndef HYDROGEN_WINDOWDATA_H
#define HYDROGEN_WINDOWDATA_H

#include "glm/vec3.hpp"

namespace Engine{
    struct WindowData{
        glm::vec3 cameraPos =   glm::vec3(0.0f, 0.0f, 5.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp =    glm::vec3(0.0f, 1.0f, 0.0f);

        bool firstMouse = true;
        bool rightButtonPressed = false;
        float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
        float pitch =  0.0f;
        float lastX =  800.0f / 2.0;
        float lastY =  600.0 / 2.0;
        float fov   =  45.0f;
        float speed =  2.5f;
    };
}


#endif //HYDROGEN_WINDOWDATA_H
