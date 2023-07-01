#ifndef HYDROGEN_SHADER_H
#define HYDROGEN_SHADER_H


#include <string>

class Shader {
private:
    static std::string readShader(const std::string& filename);
    static unsigned int compileShader(unsigned int shaderFlag, const char *shaderSource);
    void linkProgram() const;
public:
    Shader(const std::string& vertName, const std::string& fragName);
    void use() const;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
private:
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int ID;
};


#endif //HYDROGEN_SHADER_H
