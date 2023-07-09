#ifndef HYDROGEN_MODEL_H
#define HYDROGEN_MODEL_H



#include "include.h"
#include "Mesh.h"
#include "Shader.h"

#include "Texture.h"
#include "TextureArray.h"
#include "BuffersArray_AOS.h"
#include "Camera.h"

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