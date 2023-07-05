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

class Model {
private:

    glm::mat4 getModelMatrix();

public:
    Model(const std::shared_ptr<Shader>& _shader);
    void Draw(const std::shared_ptr<Camera>& _camera);
    void writeBuffers();

    void loadMesh(std::unique_ptr<Mesh> _mesh);
    void loadTexture(const std::shared_ptr<Texture>& _texture);

    void prepareTextures();
private:
    // model data
    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<BuffersArray_AOS> vertexBuffers;
    std::unique_ptr<TextureArray> texArray;
    std::shared_ptr<Shader> shader;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

};


#endif //HYDROGEN_MODEL_H