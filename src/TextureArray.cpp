#include <memory>
#include "TextureArray.h"
#include "glad/glad.h"

TextureArray::TextureArray() {

}

TextureArray::~TextureArray() {

}

void TextureArray::addTexture(const std::shared_ptr<Texture>& texture) {
    textures.push_back(texture);
}

void TextureArray::bindAllTextures() {
    for (int i = 0; i < textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i]->bindTexture();
    }
}

void TextureArray::useTextures(Shader* shader) {
    shader->use();
    for (int i = 0; i < textures.size(); ++i) {
        shader->setInt(textures[i]->getName(), i);
    }
}
