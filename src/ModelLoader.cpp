#include <iostream>
#include "ModelLoader.h"

ModelLoader::ModelLoader() {

}

ModelLoader::~ModelLoader() {

}

std::vector<std::unique_ptr<Model>> ModelLoader::loadFile(const std::string &fileName, const std::shared_ptr<Shader>& _baseShader) {

    objects.clear();
    auto filePath = "assets/models/" + fileName;

    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        exit(EXIT_FAILURE);
    }
    directory = fileName.substr(0, fileName.find_last_of('/'));

    processNode(scene->mRootNode, scene, _baseShader);
    return std::move(objects);
}

void ModelLoader::processNode(aiNode *node, const aiScene *scene, const std::shared_ptr<Shader>& _baseShader) {
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *rawMesh = scene->mMeshes[node->mMeshes[i]];

        auto mesh_textures = processMesh(rawMesh, scene);
        auto object = std::make_unique<Model>(_baseShader);
        object->loadMesh(std::move(mesh_textures.first));
        object->writeBuffers();
        for (const auto& a : mesh_textures.second) {
            object->loadTexture(a);
        }
        object->prepareTextures();
        objects.push_back(std::move(object));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, _baseShader);
    }
}

std::pair<
            std::unique_ptr<Mesh>,
            std::vector<std::shared_ptr<Texture>>
        > ModelLoader::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> uv;
    std::vector<std::shared_ptr<Texture>> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        vertices.push_back((float)mesh->mVertices[i].x);
        vertices.push_back((float)mesh->mVertices[i].y);
        vertices.push_back((float)mesh->mVertices[i].z);

        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            uv.push_back(mesh->mTextureCoords[0][i].x);
            uv.push_back(mesh->mTextureCoords[0][i].y);
        } else{
            uv.push_back(0.0f);
            uv.push_back(0.0f);
        }

    }

    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process material
    if(mesh->mMaterialIndex >= 0)
    {
        textures.clear();
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<std::shared_ptr<Texture>> diffuseMaps = loadMaterialTextures(material,
                                                           aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }

    return {std::make_unique<Mesh>(vertices, indices, uv), textures};
}

std::vector<std::shared_ptr<Texture>> ModelLoader::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName) {
    std::vector<std::shared_ptr<Texture>> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        auto texture = std::make_shared<Texture>(typeName + "_" + std::to_string(i), str.C_Str(), GL_RGBA);
        textures.push_back(texture);
    }
    return textures;
}
