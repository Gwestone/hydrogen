#ifndef HYDROGEN_MESH_H
#define HYDROGEN_MESH_H

#include "include.h"

#include "Vertex.h"
#include "BuffersArray_AOS.h"
#include "TextureArray.h"

namespace Engine{
    struct Mesh {
    private:
        void writeGPUBuffers();
    public:
        Mesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices, const std::vector<Texture> &_textures);
        ~Mesh();

        void Draw(const Shader &shader);

    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        TextureArray texManager;
        //TODO write implementation of vertex arrays management class
        //std::unique_ptr<BuffersArray_AOS> bufferArray;

        unsigned int VAO, VBO, EBO;
    };

}

#endif //HYDROGEN_MESH_H
