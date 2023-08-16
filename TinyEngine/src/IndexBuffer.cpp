#include "IndexBuffer.h"
#include "Renderer.h"

namespace TE
{
    IndexBuffer::IndexBuffer(const void* data, unsigned count)
        : Count(count)
    {
        glGenBuffers(1, &Id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &Id);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
