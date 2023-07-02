#ifndef HYDROGEN_TEXTURE_H
#define HYDROGEN_TEXTURE_H


#include <vector>
#include <string>

class Texture {
private:
public:
    Texture(const std::string &name, unsigned int sourceImageFormat);
    void loadTexture(const std::string &name, unsigned int sourceImageFormat);
    void bindTexture();
private:
    unsigned int textureID;
    unsigned int width, height, nrChannels;
};


#endif //HYDROGEN_TEXTURE_H
