#include "Texture.h"

#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace TE
{
    Texture::Texture(const char* path)
        : Path(path)
    {
        stbi_set_flip_vertically_on_load(1);
        Buffer = stbi_load(path, &Width, &Height, &ChannelCount, 0);
        glGenTextures(1, &Id);
        Bind();
        // glBindTexture(GL_TEXTURE_2D,Id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if(Buffer)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Buffer);
            // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Buffer);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(Buffer);
            // Unbind();
        }
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &Id);
    }

    void Texture::Bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D,Id);
    }

    void Texture::Unbind() const
    {
            glBindTexture(GL_TEXTURE_2D, 0);
    }
}
