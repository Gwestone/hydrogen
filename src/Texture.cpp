#include <iostream>
#include "Texture.h"
#include "glad/glad.h"
#include "stb_image.h"

Texture::Texture(const std::string &name, unsigned int sourceImageFormat) {
    loadTexture(name, sourceImageFormat);
}

void Texture::loadTexture(const std::string &name, unsigned int sourceImageFormat) {
    //load and process texture data
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int _width, _height, _nrChannels;
    unsigned char *data = stbi_load(std::string("assets/textures/" + name).c_str(), &_width, &_height, &_nrChannels, 0);
    if (data)
    {
        width = _width;
        height = _height;
        nrChannels = _nrChannels;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, sourceImageFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Texture::bindTexture() {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

