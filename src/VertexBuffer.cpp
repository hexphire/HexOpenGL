#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));   //create vertex buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); //make buffer active "bind" it.
    GLCall(glBufferData(GL_ARRAY_BUFFER, size , data, GL_STATIC_DRAW)); //place data into buffer, along with some basic size and use case info

}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

unsigned int VertexBuffer::getBuffer() const
{
    return m_RendererID;
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID))
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0))
}
