#pragma once

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError(); \
					x; \
					ASSERT(GLLogCall(#x, __LINE__))

/*�ڻ�ȡ���������ǰ���֮ǰ�Ĵ�����*/
void GLClearError();
bool GLLogCall(const char* function, int line);