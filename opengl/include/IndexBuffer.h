#pragma once
#include "common.h"

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int count, unsigned int bufferType = GL_STATIC_DRAW);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	unsigned int getCount() const { return m_count; }
private:
	unsigned int m_BufferType;
	unsigned int m_RenderId;
	unsigned int m_count;
};