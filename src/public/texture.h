#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture
{
public:
    unsigned int ID;
private:
    int width, height, nrChannels;

public:
    Texture();
    Texture(const char* pathToImage);
    Texture(const char* pathToImage, unsigned int textureUnit, GLenum wrapMode);

    void SetTextureUnit(unsigned int textureUnit);

};
#endif