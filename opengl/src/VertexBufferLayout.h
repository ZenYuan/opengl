#pragma once

#include <GL/glew.h>
#include <vector>

struct VertexBufferElement
{
	VertexBufferElement(unsigned int _type, unsigned int _count, bool _normalized, size_t _stride) :
		type(_type), count(_count), normalized(_normalized), stride(_stride) {}

	unsigned int type;
	unsigned int count;
	bool normalized;
	size_t stride;

	static size_t GetSizeOfType(unsigned int type) {
		return sizeof(type);
	}
};

/*每个buffer含有多个element,组成一个场景的layout*/
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
		m_Elements.emplace_back(GL_FLOAT, count, GL_FALSE, m_stride);
	}

	template<>
	void Push<unsigned int>(unsigned int count) 
	{
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		m_Elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE, m_stride);
	}

	template<>
	void Push<unsigned char>(unsigned int count) 
	{
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		m_Elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_FALSE, m_stride);
	}

	inline const auto& GetElements() const { return m_Elements; }
	
private:
	std::vector<VertexBufferElement> m_Elements;
	size_t m_stride;

};