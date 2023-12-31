﻿#pragma once
#include <vector>
#include <glad/glad.h>

#include "Core.h"

namespace TE
{
    struct TE_API VertexBufferElement
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
    
    class TE_API VertexBufferLayout
    {
    public:
        VertexBufferLayout()
            : stride(0)
        {            
        }

        template<typename T>
        void Add(unsigned int count)
        {
            static_assert(false);
        }

        template<typename T>
        void Add(std::vector<unsigned int> counts)
        {
            for (unsigned int count : counts)
            {
                Add<T>(count);
            }
        }

        template<>
        void Add<float>(unsigned int count)
        {
            elements.push_back({GL_FLOAT, count, GL_FALSE});
            stride += count * sizeof(GL_FLOAT); 
        }

        template<>
        void Add<unsigned int>(unsigned int count)
        {
            elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
            stride += count * sizeof(GL_UNSIGNED_INT); 
        }
        
        template<>
        void Add<unsigned char>(unsigned int count)
        {
            elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
            stride += count * sizeof(GL_UNSIGNED_BYTE); 
        }

        inline std::vector<VertexBufferElement> GetElements() const { return elements; }
        inline unsigned int GetStride() const { return stride; }
        
        
    private:
        unsigned int stride;
        std::vector<VertexBufferElement> elements;
    };

}
