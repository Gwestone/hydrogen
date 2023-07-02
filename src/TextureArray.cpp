#include "TextureArray.h"
#include "glad/glad.h"

TextureArray::TextureArray() {

}

TextureArray::~TextureArray() {

}

void TextureArray::addTexture(Texture* texture) {
    textures.push_back(texture);
}

void TextureArray::bindAllTextures() {
    for (int i = 0; i < textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i]->bindTexture();
    }
}

void TextureArray::useTextures(const Shader &shader) {
    shader.use();
    for (int i = 0; i < textures.size(); ++i) {
        shader.setInt(textures[i]->getName(), i);
    }
}
