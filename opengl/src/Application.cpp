#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Render.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

struct ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};
/*get shader source from file*/
static ShaderSource ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	std::string line;

	enum class ShaderType : int8_t
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	ShaderType type = ShaderType::NONE;
	std::stringstream ss[2];

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return {ss[0].str(), ss[1].str()};
}

static unsigned int CompilerShader(unsigned int type, const std::string& shaderSource)
{
	unsigned int id = 0;
	id = glCreateShader(type);
	const char* src = shaderSource.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)alloca(sizeof(char)* length);
		glGetShaderInfoLog(id, length, nullptr, log);
		std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader error:";
		std::cout << log << std::endl;
		glDeleteShader(id);
	}
	return id;
}


static unsigned int CreateShaderProgream(const std::string& VertexSource, const std::string& FrgamentShader)
{
	unsigned int vs = CompilerShader(GL_VERTEX_SHADER, VertexSource);
	unsigned int fs = CompilerShader(GL_FRAGMENT_SHADER, FrgamentShader);

	unsigned int progream = glCreateProgram();
	glAttachShader(progream, vs);
	glAttachShader(progream, fs);
	glLinkProgram(progream);
	
	glDeleteShader(vs);
	glDeleteShader(fs);
	return progream;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	/*修改刷新间隔*/
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "error" << std::endl;
	}

	float vertices[] =
	{
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};

	/*unsigned int 是opengl要求索引缓冲区设定，否则无法绘制*/
	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	//scope 方便释放资源
	{
		//保存vertex Attribute,无需每次渲染切换layout;
		VertexArray va;
		VertexBuffer vb(vertices, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		ShaderSource source = ParseShader("res/shaders/Basics.shader");
		unsigned int progream = CreateShaderProgream(source.VertexSource, source.FragmentSource);

		int location = glGetUniformLocation(progream, "u_Color");
		float r = 0.0f;

		glUseProgram(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(progream);
			GLCall(glUniform4f(location, rand() % 10 / 10.0f, 0.2, 0.3, 0.1));
			
			va.Bind();
			ib.Bind();

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}