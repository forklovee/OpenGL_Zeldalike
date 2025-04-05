#ifndef SHADER_H
#define SHADER_H
#endif

#include <glad/glad.h>
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
    void SetVec4Parameter(const std::string &name, float x, float y, float z, float w);

private:
    const std::string GetShaderCodeString(const char* shaderFilePath);
    unsigned int CompileShader(GLenum shaderType, const char* shaderCode);
    void LinkShaders(int shadersToLink, unsigned int shaderIDs[2]);
};


