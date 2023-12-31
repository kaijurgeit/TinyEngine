﻿#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

namespace TE
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &id);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &id);
    }

    void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
    {
        vb.Bind();
        const std::vector<VertexBufferElement>& elements = layout.GetElements();
        unsigned int offset = 0;
        for (int i = 0; i < elements.size(); ++i)
        {
            const auto& element = elements[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.Count, element.Type, element.Normalized,
                layout.GetStride(), reinterpret_cast<const void*>(offset));
            offset += element.Count * sizeof(element.Type);
        }
    }

    void VertexArray::Bind() const
    {  
        glBindVertexArray(id);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

}
