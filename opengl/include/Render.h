#pragma once

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError(); \
					x; \
					ASSERT(GLLogCall(#x, __LINE__))

/*在获取任意错误码前清除之前的错误码*/
void GLClearError();
bool GLLogCall(const char* function, int line);


class VertexArray;
class IndexBuffer;
class Shader;
class Render
{
public:
	void Renderprocess(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};