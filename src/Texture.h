#ifndef HYDROGEN_TEXTURE_H
#define HYDROGEN_TEXTURE_H


#include <vector>
#include <string>
#include "glad/glad.h"

class Texture {
private:
    static GLenum getFormat(unsigned int nrComponents);
public:
    Texture(const std::string &name, const std::string &fileName);
    ~Texture();

    void loadTexture(const std::string &_name, const std::string &fileName);
    void bindTexture();
    std::string getName();
private:
    unsigned int textureID;
    unsigned int width, height, nrChannels;
    std::string name;
public:
    std::string type;
    std::string path;
};


#endif //HYDROGEN_TEXTURE_H
