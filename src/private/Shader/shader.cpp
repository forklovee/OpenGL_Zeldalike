#include "Shader/shader.h"

#include <type_traits>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <iostream>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    const std::string vShaderCodeString = GetShaderCodeString(vertexShaderPath);
    const std::string fShaderCodeString = GetShaderCodeString(fragmentShaderPath);

    unsigned int shaders[] = {
        CompileShader(GL_FRAGMENT_SHADER, fShaderCodeString.c_str()),
        CompileShader(GL_VERTEX_SHADER, vShaderCodeString.c_str())
    };

    LinkShaders(2, shaders);
}

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::SetMat4Parameter(const std::string &name, glm::mat4 mat)
{
    int modulateLocation = glGetUniformLocation(ID, name.c_str());
    if (modulateLocation > -1)
    {
        glUseProgram(ID);
        glUniformMatrix4fv(modulateLocation, 1, GL_FALSE, glm::value_ptr(mat));
    }
    Use();
}

void Shader::SetVec4Parameter(const std::string &name, glm::vec4 vec)
{
    int modulateLocation = glGetUniformLocation(ID, name.c_str());
    if (modulateLocation > -1)
    {
        glUseProgram(ID);
        glUniform4f(modulateLocation, vec.x, vec.y, vec.z, vec.w);
    }
    Use();
}

void Shader::SetIntParameter(const std::string &name, int value)
{
    int modulateLocation = glGetUniformLocation(ID, name.c_str());
    if (modulateLocation > -1)
    {
        glUseProgram(ID);
        glUniform1i(modulateLocation, value);
    }
    Use();
}

template <typename T>
void Shader::SetParameter(const std::string &name, T value)
{
    int modulateLocation = glGetUniformLocation(ID, name.c_str());
    if (modulateLocation > -1)
    {
        glUseProgram(ID);
        if (std::is_same<T, float>::value){
            glUniform1f(modulateLocation, value);
        }
        else if (std::is_same<T, int>::value)
        {
            glUniform1i(modulateLocation, value);
        }
        else{
            glUniform1i(modulateLocation, value);
        }
    }
    Use();
}

const std::string Shader::GetShaderCodeString(const char* shaderFilePath)
{
    std::string shaderCodeString;
    std::ifstream shaderFile;

    // ensure exception throwing
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open shader files
        shaderFile.open(shaderFilePath);
        // write files buffer to streams
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        // convert stream to string
        shaderCodeString = shaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        printf("%sERROR::SHADER::FILE_UNREADABLE\n", "\x1B[31m");
    }

    return shaderCodeString;
}

unsigned int Shader::CompileShader(GLenum shaderType, const char *shaderCode)
{
    // Define and compile Vertex Shader
    unsigned int shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &shaderCode, NULL);
    glCompileShader(shaderID);

    int shaderCompileSuccess;
    char shaderCompileInfoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompileSuccess);
    if (!shaderCompileSuccess)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, shaderCompileInfoLog);
        printf("%sERROR::SHADER::COMPILATION_FAILED: %s\n%s", "\x1B[31m", shaderCompileInfoLog, shaderCode);
    }

    return shaderID;
}

void Shader::LinkShaders(int shadersToLink, unsigned int shaderIDs[2])
{
    //Combine Vertex and Fragment shader to one program.
    ID = glCreateProgram();

    for(int i=0; i<shadersToLink; i++)
    {
        glAttachShader(ID, shaderIDs[i]);
    }
    
    glLinkProgram(ID);
    int shaderProgramCompileSuccess;
    char shaderProgramCompileInfoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &shaderProgramCompileSuccess);
    if (!shaderProgramCompileSuccess)
    {
        glGetProgramInfoLog(ID, 512, NULL, shaderProgramCompileInfoLog);
        printf("ERROR::SHADER::PROGRAM::LINK_FAILED: %s\n", shaderProgramCompileInfoLog);
    }

    Use();

    for(int i=0; i<shadersToLink; i++)
    {
        glDeleteShader(shaderIDs[i]);
    }
}
