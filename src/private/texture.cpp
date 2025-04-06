#include "texture.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{
}

Texture::Texture(const char *pathToImage)
{
    Texture(pathToImage, 0, GL_REPEAT);
}

Texture::Texture(const char *pathToImage, unsigned int textureUnit, GLenum wrapMode)
{
    // load image data
    unsigned char* data = stbi_load(pathToImage, &width, &height, &nrChannels, 0);

    // generate and bind texture
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, ID);
    // Set texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    // Set border color for Clamp to border.
    float borderColor[] = { 1.f, 0.f, 1.f, 1.f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // Set texture filtering (min = nearest, mag = linear)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data)
    {
        // create texture from raw data
        glTexImage2D(GL_TEXTURE_2D, // target
            0, // mipmap level (0 = base)
            GL_RGB, // target texture color format
            width, height,
            0, // should always be 0 [legacy stuff???]
            GL_RGB, // source image color format
            GL_UNSIGNED_BYTE, // source data type
            data // data itself
        );

        // generate mipmaps \
        if i had a whole lot of time... \
        i would have specify all different images manually by incrementing the second argument \
        but luckily we've got this little guy: 
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("%sERROR::TEXTURE::FAILED_TO_LOAD_TEXTURE", "\x1B[31m");
    }
    
    SetTextureUnit(textureUnit);

    stbi_image_free(data);
}

void Texture::SetTextureUnit(unsigned int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, ID);
}
