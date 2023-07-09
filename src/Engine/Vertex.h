#ifndef HYDROGEN_VERTEX_H
#define HYDROGEN_VERTEX_H

#include "include.h"

namespace Engine{
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

}

#endif //HYDROGEN_VERTEX_H
