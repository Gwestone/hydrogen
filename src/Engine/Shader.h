#ifndef HYDROGEN_SHADER_H
#define HYDROGEN_SHADER_H

#include "include.h"

namespace Engine{
    class Shader {
    private:
        static std::string readShader(const std::string& filename);
        static unsigned int compileShader(unsigned int shaderFlag, const char *shaderSource);
        void linkProgram() const;
    public:
//    Shader (const Shader&) = delete;
//    Shader& operator= (const Shader&) = delete;

        Shader(){};
        Shader(const std::string& vertName, const std::string& fragName);
        void loadShaders(const std::string& vertName, const std::string& fragName);
        void use() const;

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec3(const std::string &name, glm::vec3 value) const;
        void setMatrix4x4(const std::string &name, glm::mat4 trans) const;
    private:
        unsigned int vertexShader;
        unsigned int fragmentShader;
        unsigned int ID;
    };

}

#endif //HYDROGEN_SHADER_H
