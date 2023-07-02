#ifndef HYDROGEN_TEXTUREARRAY_H
#define HYDROGEN_TEXTUREARRAY_H

#include "Texture.h"
#include "Shader.h"

class TextureArray {
private:
public:
    TextureArray (const TextureArray&) = delete;
    TextureArray& operator= (const TextureArray&) = delete;

    TextureArray();
    ~TextureArray();
    void addTexture(Texture* texture);
    void bindAllTextures();
    void useTextures(const Shader& shader);
private:
    std::vector<Texture*> textures;
};

#endif //HYDROGEN_TEXTUREARRAY_H
