#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"

namespace Engine {
    Texture::Texture(const std::string &name, const std::string &fileName) {
        loadTexture(name, fileName);
    }

    Texture::~Texture() {

    }

    void Texture::loadTexture(const std::string &_name, const std::string &fileName) {
        //load and process texture data
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // load and generate the texture
        int _width, _height, _nrChannels;
        unsigned char *data = stbi_load(fileName.c_str(), &_width, &_height, &_nrChannels, 0);
        if (data) {
            name = _name;
            width = _width;
            height = _height;
            nrChannels = _nrChannels;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, getFormat(nrChannels), GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture " << fileName << std::endl;
        }
        stbi_image_free(data);
    }

    void Texture::bindTexture() {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    std::string Texture::getName() {
        return name;
    }

    GLenum Texture::getFormat(unsigned int nrComponents) {
        if (nrComponents == 1)
            return GL_RED;
        else if (nrComponents == 2)
            return GL_RG;
        else if (nrComponents == 3)
            return GL_RGB;
        else if (nrComponents == 4)
            return GL_RGBA;
        return GL_RED;
    }
}