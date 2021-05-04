#pragma once

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError(); \
					x; \
					ASSERT(GLLogCall(#x, __LINE__))

/*在获取任意错误码前清除之前的错误码*/
void GLClearError();
bool GLLogCall(const char* function, int line);