#include "VertexBuffer.h"
#include "GL/glew.h"
#include "Render.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int bufferType)
	:m_BufferType(bufferType)
{
	GLCall(glGenBuffers(1, &m_RenderId));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderId));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, m_BufferType));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RenderId));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderId));
}

void VertexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
