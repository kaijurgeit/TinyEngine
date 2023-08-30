#include "VertexBuffer.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace TE
{
    VertexBuffer::VertexBuffer(const void* data, unsigned size)
    {
        glGenBuffers(1, &id);
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &id);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
