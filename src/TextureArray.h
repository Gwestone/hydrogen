#ifndef HYDROGEN_TEXTUREARRAY_H
#define HYDROGEN_TEXTUREARRAY_H

#include "Texture.h"
#include "Shader.h"
#include <memory>

class TextureArray {
private:
public:
    TextureArray (const TextureArray&) = delete;
    TextureArray& operator= (const TextureArray&) = delete;

    TextureArray();
    ~TextureArray();
    void addTexture(const std::shared_ptr<Texture>& texture);
    void bindAllTextures();
    void useTextures(Shader* shader);
private:
    std::vector<std::shared_ptr<Texture>> textures;
};

#endif //HYDROGEN_TEXTUREARRAY_H
