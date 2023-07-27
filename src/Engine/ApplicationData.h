#ifndef HYDROGEN_APPLICATIONDATA_H
#define HYDROGEN_APPLICATIONDATA_H

#include "include.h"

namespace Engine{
    struct ApplicationData{
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

        int height = 600, width = 800;
    };
}


#endif //HYDROGEN_APPLICATIONDATA_H
