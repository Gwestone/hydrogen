#include "Model.h"

Model::Model(const std::shared_ptr<Shader>& _shader) {
    texArray = std::make_unique<TextureArray>();
    vertexBuffers = std::make_unique<BuffersArray_AOS>();
    shader = _shader;
}

glm::mat4 Model::getModelMatrix() {
    auto model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.x, {1.0, 0.0, 0.0});
    model = glm::rotate(model, rotation.y, {0.0, 1.0, 0.0});
    model = glm::rotate(model, rotation.z, {0.0, 0.0, 1.0});
    return model;
}

void Model::writeBuffers() {
    unsigned int vertex_buffer = vertexBuffers->createBuffer();
    vertexBuffers->writeBuffer(0, vertex_buffer, mesh->getRawVertices(), mesh->getVerticesSize(), 3);

    unsigned int uv_buffer = vertexBuffers->createBuffer();
    vertexBuffers->writeBuffer(1, uv_buffer, mesh->getRawUV(), mesh->getUVSize(), 2);

    vertexBuffers->createElementBuffer();
    vertexBuffers->writeElementBuffer(mesh->getRawIndices(), mesh->getIndicesSize());
}

void Model::Draw(const std::shared_ptr<Camera>& _camera) {

    auto trans = _camera->getCameraMatrix() * getModelMatrix();
//    auto trans = glm::mat4(1.0f);
//    auto trans = _camera->getCameraMatrix();

    texArray->bindAllTextures();
    vertexBuffers->bind();
    shader->use();

    shader->setMatrix4x4("transform", trans);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void Model::loadMesh(std::unique_ptr<Mesh> _mesh) {
    mesh = std::move(_mesh);
}

void Model::loadTexture(const std::shared_ptr<Texture>& _texture) {
    texArray->addTexture(_texture);
}

void Model::prepareTextures() {
    texArray->useTextures(shader.get());
}