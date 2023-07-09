#ifndef HYDROGEN_MODEL_H
#define HYDROGEN_MODEL_H


#include <string>
#include <memory>
#include "Mesh.h"
#include "Shader.h"
#include "assimp/scene.h"
#include "Texture.h"
#include "TextureArray.h"
#include "BuffersArray_AOS.h"
#include "Camera.h"
#include "glad/glad.h"
#include <iostream>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace Engine{
    class Model {
    private:

        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);

    public:
        Model(){};
        Model(const std::string& path);
        ~Model();
        void Draw(const Shader &shader);
        void loadModel(const std::string& path);
    private:

        // model data
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<Texture> textures_loaded;

    };
}


#endif //HYDROGEN_MODEL_H