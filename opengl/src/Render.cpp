#include "common.h"
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

void Render::Renderprocess(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, DrawType drawType) const
{
	va.Bind();
	shader.Bind();
	if (DrawType::INDEX == drawType)
	{
		ib.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
		ib.UnBind();
	}
	else if(DrawType::ARRAY == drawType)
	{
		GLCall(glDrawArrays(GL_TRIANGLES, 0, m_count));
	}
	va.UnBind();
}

