#pragma once

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError(); \
					x; \
					ASSERT(GLLogCall(#x, __LINE__))

/*�ڻ�ȡ���������ǰ���֮ǰ�Ĵ�����*/
void GLClearError();
bool GLLogCall(const char* function, int line);


class VertexArray;
class IndexBuffer;
class Shader;
class Render
{
public:
	static void Renderprocess(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
};