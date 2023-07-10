#include "Shader.h"
#include "Log.h"

namespace Engine{
    Shader::Shader(const std::string &vertName, const std::string &fragName) {
        loadShaders(vertName, fragName);
    }

    void Shader::loadShaders(const std::string &vertName, const std::string &fragName) {
        std::string vertexShaderSource = readShader(vertName);
        vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
        // fragment shader
        std::string fragmentShaderSource = readShader(fragName);
        fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());
        // link shaders
        ID = glCreateProgram();
        linkProgram();

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }


    void Shader::use() const {
        glUseProgram(ID);
    }

    void Shader::setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setVec3(const std::string &name, glm::vec3 value) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
    }

    void Shader::setMatrix4x4(const std::string &name, glm::mat4 trans) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
    }

    void Shader::linkProgram() const {
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        // check for linking errors
        int success;
        char infoLog[512];
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            HY_ENGINE_ERROR("Failed Shader linking: {0} .", infoLog);
        }
    }


    std::string Shader::readShader(const std::string &filename) {
        std::string shaderSource;
        std::ifstream shaderFile;
        try
        {
            // open files
            shaderFile.open("assets/shaders/" + filename);
            std::stringstream shaderStream;
            // read file's buffer contents into streams
            shaderStream << shaderFile.rdbuf();
            // close file handlers
            shaderFile.close();
            // convert stream into string
            shaderSource = shaderStream.str();
        }
        catch(std::ifstream::failure e)
        {
            HY_ENGINE_ERROR("Failed Shader reading.");
        }
        return shaderSource;
    }

    unsigned int Shader::compileShader(unsigned int shaderFlag, const char *shaderSource) {
        unsigned int shader = glCreateShader(shaderFlag);
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            HY_ENGINE_ERROR("Failed Shader compilation: {0} .", infoLog);
            return -1;
        } else{
            return shader;
        }
    }

}
