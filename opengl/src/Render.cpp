#include "GL/glew.h"
#include "iostream"
#include "Render.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL error]" << "(" << error << ")" << " "
			<< "func:" << function << " " << "line:" << line << std::endl;
		return false;
	}
	return true;
}