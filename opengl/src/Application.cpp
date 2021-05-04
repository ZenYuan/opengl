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
#include "Shader.h"


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
	glfwSwapInterval(5);

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

		Shader shader("res/shaders/Basics.shader");
		shader.Bind();

		float r = 0.0f;

		shader.UnBind();
		vb.UnBind();
		ib.UnBind();
		va.UnBind();

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			
			shader.Bind();
			glm::vec4 color = glm::vec4(rand() % 10 / 10.0f, 0.2, 0.3, 0.1);
			shader.SetUniform4f("u_Color", color);
			
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