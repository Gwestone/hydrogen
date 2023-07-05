#ifndef HYDROGEN_MODELLOADER_H
#define HYDROGEN_MODELLOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include "Mesh.h"
#include "Model.h"

class ModelLoader {
private:
    void processNode(aiNode *node, const aiScene *scene, const std::shared_ptr<Shader>& _baseShader);
    std::pair<std::unique_ptr<Mesh>,std::vector<std::shared_ptr<Texture>>> processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         const std::string& typeName);
public:
    ModelLoader();
    ~ModelLoader();
    std::vector<std::unique_ptr<Model>> loadFile(const std::string& fileName, const std::shared_ptr<Shader>& _baseShader);
private:
    std::vector<std::unique_ptr<Model>> objects;
    std::string directory;
};


#endif //HYDROGEN_MODELLOADER_H
