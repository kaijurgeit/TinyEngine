#include "Texture.h"

#include "glad/glad.h"
#include "stb_image.h"

namespace TE
{
    Texture::Texture(const char* path)
    {
        // stbi_set_flip_vertically_on_load(1);
        // LocalBuffer = stbi_load(path, &Width, &Height, &ChannelCount);
        // glGenTextures(1, &Id);
        // glBindTexture(GL_TEXTURE_2D,Id);
    }

    Texture::~Texture()
    {
    }

    void Texture::Bind() const
    {
    }

    void Texture::Unbind() const
    {
    }
}
