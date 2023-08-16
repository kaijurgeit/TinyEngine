#pragma once

namespace TE
{
    class VertexBuffer
    {
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
        
    private:
        unsigned int Id;
    };    
}
