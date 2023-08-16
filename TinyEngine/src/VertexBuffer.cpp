#include "VertexBuffer.h"
#include "Renderer.h"

namespace TE
{
    VertexBuffer::VertexBuffer(const void* data, unsigned size)
    {
        glGenBuffers(1, &Id);
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &Id);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, Id);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
