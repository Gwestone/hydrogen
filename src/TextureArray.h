#ifndef HYDROGEN_TEXTUREARRAY_H
#define HYDROGEN_TEXTUREARRAY_H

#include "Texture.h"
#include "Shader.h"
#include <memory>

class TextureArray {
private:
public:

    TextureArray();
    ~TextureArray();
    void addTexture(const Texture& texture);
    void bindAllTextures();
    void useTextures(const Shader &shader);
private:
    std::vector<Texture> textures;
};

#endif //HYDROGEN_TEXTUREARRAY_H
