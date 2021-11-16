#pragma once


class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size, unsigned int bufferType);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
private:
	unsigned int m_BufferType;
	unsigned int m_RenderId;
};