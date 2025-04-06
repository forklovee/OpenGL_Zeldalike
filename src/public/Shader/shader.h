#ifndef SHADER_H
#define SHADER_H
#endif

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>

class Shader
{
public:
    // program id
    unsigned int ID;

public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    void Use();
    template<typename T> void SetParameter(const std::string &name, T value);
    void SetMat4Parameter(const std::string &name, glm::mat4 mat);
    void SetVec4Parameter(const std::string &name, glm::vec4 vec);
    void SetIntParameter(const std::string &name, int value);

private:
    const std::string GetShaderCodeString(const char* shaderFilePath);
    unsigned int CompileShader(GLenum shaderType, const char* shaderCode);
    void LinkShaders(int shadersToLink, unsigned int shaderIDs[2]);
};


