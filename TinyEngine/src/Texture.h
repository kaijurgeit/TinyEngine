#pragma once
#include <string>

namespace TE
{
    class Texture
    {
        friend class Model;
    public:
        Texture(const std::string& path);
        Texture(const char* path);
        ~Texture();
        Texture(const Texture&) = default;
        Texture(Texture&&) = default;
        Texture& operator=(const Texture&) = default;
        Texture& operator=(Texture&&) = default;

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;
        
        unsigned GetId() const { return id; }
        std::string GetType() const { return type; }
        std::string GetPath() const { return path; }
        
    private:
        unsigned int id;
        std::string path;
        std::string type;
        unsigned char* buffer = nullptr;
        int width = 0;
        int height = 0;
        int channelCount = 0;
        int bitsPerPixel = 0;
    };
}
