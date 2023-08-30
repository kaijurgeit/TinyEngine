#include "Texture.h"

#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

#include "stb_image.h"

namespace TE
{
    Texture::Texture(const std::string& path)
        : Texture(path.c_str())
    {
        
    }

    Texture::Texture(const char* path)
        : path(path)
    {
        stbi_set_flip_vertically_on_load(1);
        buffer = stbi_load(path, &width, &height, &channelCount, 0);
        
        if(!buffer)
        {
            std::cerr << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(buffer);
            return;
        }

        GLenum format;

        switch (channelCount)
        {
            case 1: format = GL_RED; break;
            case 3: format = GL_RGB; break;
            case 4: format = GL_RGBA; break;
            default: format = GL_RGB;
        }
        
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D,id);
        
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer);        
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(buffer);
    }

    Texture::~Texture()
    {
        // glDeleteTextures(1, &id);
    }

    void Texture::Bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D,id);
    }

    void Texture::Unbind() const
    {
            glBindTexture(GL_TEXTURE_2D, 0);
    }
}
