#pragma once
#include <vector>
#include <glad/glad.h>

#include "Core.h"

namespace TE
{
    struct VertexBufferElement
    {
        unsigned int Type;
        unsigned int Count;
        unsigned char Normalized;

        static unsigned int GetSizeOfType(unsigned int type)
        {
            switch (type)
            {
            case GL_FLOAT:          return 4;                
            case GL_UNSIGNED_INT:   return 4;                
            case GL_UNSIGNED_BYTE:  return 1;          
            }
            return 0;
        }
    };
    
    class VertexBufferLayout
    {
    public:
        VertexBufferLayout()
            : Stride(0)
        {
            
        }

        template<typename T>
        void Add(unsigned int count)
        {
            static_assert(false);
        }

        template<>
        void Add<float>(unsigned int count)
        {
            Elements.push_back({GL_FLOAT, count, GL_FALSE});
            Stride += count * sizeof(GL_FLOAT); 
        }

        template<>
        void Add<unsigned int>(unsigned int count)
        {
            Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
            Stride += count * sizeof(GL_UNSIGNED_INT); 
        }
        
        template<>
        void Add<unsigned char>(unsigned int count)
        {
            Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
            Stride += count * sizeof(GL_UNSIGNED_BYTE); 
        }

        inline std::vector<VertexBufferElement> GetElements() const { return Elements; }
        inline unsigned int GetStride() const { return Stride; }
        
        
    private:
        unsigned int Stride;
        std::vector<VertexBufferElement> Elements;
    };

}
