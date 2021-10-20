#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, VertexBufferLayout& element);

	void Bind() const;
	void UnBind() const;
private:
	unsigned int m_RenderId;
};