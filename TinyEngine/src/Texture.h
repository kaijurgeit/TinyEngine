#pragma once
#include <string>

namespace TE
{
    class Texture
    {
    public:
        Texture(const char* path);
        ~Texture();
        Texture(const Texture&) = default;
        Texture(Texture&&) = default;
        Texture& operator=(const Texture&) = default;
        Texture& operator=(Texture&&) = default;

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;
        
    private:
        unsigned int Id;
        std::string Path;
        unsigned char* Buffer = nullptr;
        int Width = 0;
        int Height = 0;
        int ChannelCount = 0;
        int BitsPerPixel = 0;
    };
}
