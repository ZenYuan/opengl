#pragma once


class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	unsigned int getCount() const { return m_count; }
private:
	unsigned int m_RenderId;
	unsigned int m_count;
};