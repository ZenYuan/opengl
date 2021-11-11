#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Render.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define GLSL_VERSION "#version 330"

static GLFWwindow* window;
bool CreateWindow(int SwapInterval)
{
	
	/* Initialize the library */
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	/*修改刷新间隔*/
	glfwSwapInterval(SwapInterval);

	/*imgui context*/
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	/*imgui style*/
	ImGui::StyleColorsDark();

	/*Platform/Renderer backends*/
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);
	return true;
}


int main(void)
{
	CreateWindow(5);
	assert(window != nullptr);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "error" << std::endl;
	}

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f
	};

	/*unsigned int 是opengl要求索引缓冲区设定，否则无法绘制*/
	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	//glm::mat4 trans = glm::ortho();

	//scope 方便释放资源
	{
		//保存vertex Attribute,无需每次渲染切换layout;
		VertexArray va;
		VertexBuffer vb(vertices, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);   //positon
		layout.Push<float>(2);   //texture
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);
		Shader shader("res/shaders/Basics.shader");

		glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, 1.0f, -1.0f);
		Texture texture0("res/image/awesomeface.png");
		Texture texture1("res/image/killeroo-simple.jpg");


		shader.UnBind();
		vb.UnBind();
		ib.UnBind();
		va.UnBind();

		Render render;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Start new frame for Dear ImGui */
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// 1. Show the big demo window
			bool show_demo_window = true;
			ImGui::ShowDemoWindow(&show_demo_window);


			/* Render here */
			shader.Bind();
			texture0.Bind();
			shader.SetUniformi("texSampler0", 0);
			texture1.Bind(1);
			shader.SetUniformi("texSampler1", 1);

			/*MVP*/
			shader.SetUniformMatrix4f("u_mvp", proj);

			render.Renderprocess(va, ib, shader);

			/*Rendering*/
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	/* Clear */
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}