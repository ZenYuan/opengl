#include "VertexArray.h"
#include "Render.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RenderId));
	GLCall(glBindVertexArray(m_RenderId));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RenderId))
}

void VertexArray::AddBuffer(const VertexBuffer& vb, VertexBufferLayout& layout)
{
	unsigned int offset = 0;
	const auto& elements = layout.GetElements();

	Bind();
	vb.Bind();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, elements[i].stride, (void*)offset));
		GLCall(glEnableVertexAttribArray(i));
		offset += elements[i].stride;
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RenderId));
}

void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}

