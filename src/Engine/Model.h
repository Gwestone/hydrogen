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

        void setPos(const glm::vec3& _pos){pos = _pos;}
        void setScale(const glm::vec3& _scale){scale = _scale;}
        void setRotation(const glm::vec3& _rotation){rotate = _rotation;}

        glm::mat4 getModelMatrix();
    private:

        // model data
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<Texture> textures_loaded;

        glm::vec3 pos = glm::vec3(0);
        glm::vec3 scale = glm::vec3(1);
        glm::vec3 rotate = glm::vec3(0);

    };
}


#endif //HYDROGEN_MODEL_H