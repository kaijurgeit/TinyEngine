#pragma once
#include "glad/glad.h"

namespace TE
{
    class IndexBuffer
    {
    public:
        IndexBuffer(const void* data, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        inline unsigned int GetCount() const { return Count; }
        
    private:
        unsigned int Id;
        unsigned int Count;
    };    
}
