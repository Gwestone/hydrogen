#ifndef HYDROGEN_TEXTURE_H
#define HYDROGEN_TEXTURE_H


#include <vector>
#include <string>

class Texture {
private:
public:
    Texture (const Texture&) = delete;
    Texture& operator= (const Texture&) = delete;

    Texture(const std::string& name, const std::string &fileName, unsigned int sourceImageFormat);
    void loadTexture(const std::string& _name, const std::string &fileName, unsigned int sourceImageFormat);
    void bindTexture();
    std::string getName();
private:
    unsigned int textureID;
    unsigned int width, height, nrChannels;
    std::string name;
};


#endif //HYDROGEN_TEXTURE_H
