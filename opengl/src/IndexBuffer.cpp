#include "IndexBuffer.h"
#include "GL/glew.h"
#include "Render.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count):
	m_count(count)
{
	GLCall(glGenBuffers(1, &m_RenderId));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderId));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RenderId));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderId));
}

void IndexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}


