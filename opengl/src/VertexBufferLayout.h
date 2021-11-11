#pragma once

#include <GL/glew.h>
#include <vector>
#include "Render.h"

struct VertexBufferElement
{
	VertexBufferElement(unsigned int _type, unsigned int _count, bool _normalized) :
		type(_type), count(_count), normalized(_normalized) {}

	unsigned int type;
	unsigned int count;
	bool normalized;

	static size_t GetSizeOfType(unsigned int type) {
		switch (type)
		{
		case GL_FLOAT:
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		default:
			ASSERT(false);
			return 0;
		}
	}
};

/*每个buffer含有多个element(positon,texture,color),组成一个场景的layout*/
class VertexBufferLayout
{
public:
	VertexBufferLayout() :
		m_stride(0) {}

	template<typename T>
	void Push(unsigned int count) 
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) 
	{
		
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
		m_Elements.emplace_back(GL_FLOAT, count, GL_FALSE);
	}

	template<>
	void Push<unsigned int>(unsigned int count) 
	{
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		m_Elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE);
	}

	template<>
	void Push<unsigned char>(unsigned int count) 
	{
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		m_Elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_FALSE);
	}

	inline const auto& GetElements() const { return m_Elements; }
	inline const size_t GetStride() const { return m_stride; }
private:
	std::vector<VertexBufferElement> m_Elements;
	size_t m_stride;

};