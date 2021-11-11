#include "GL/glew.h"
#include "iostream"
#include "Render.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

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

void Render::Renderprocess(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	glClear(GL_COLOR_BUFFER_BIT);
	va.Bind();
	ib.Bind();
	shader.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}
