#include "common.h"
#include <GLFW/glfw3.h>
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

#include "imguicfg.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

extern GLFWwindow* CreateWindow(int SwapInterval);

#if 0
int main(void)
{
	GLFWwindow* window = CreateWindow(1);
	assert(window != nullptr);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "error" << std::endl;
	}

	float vertices[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 -0.5f, 0.5f, -0.5f,  0.0f, 1.0f
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
		VertexBuffer vb(vertices, 5 * 4 * sizeof(float));
		VertexBufferLayout layout;
		//将属性按顺序加入
		layout.Push<float>(3);   //positon
		layout.Push<float>(2);   //texture
		va.AddBuffer(vb, layout);
		IndexBuffer ib(indices, 6);

		Shader shader("../res/shaders/Basics.shader");
		Texture texture0("../res/image/awesomeface.png");
		Texture texture1("../res/image/killeroo-simple.jpg");

		shader.UnBind();
		vb.UnBind();
		ib.UnBind();
		va.UnBind();

		imguiCfg imgui(window);
		Render render;

		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			imgui.start();
			/* Render here */
			shader.Bind();
			texture0.Bind();
			shader.SetUniformi("texSampler0", 0);
			texture1.Bind(1);
			shader.SetUniformi("texSampler1", 1);

			/*MVP*/
			glm::mat4 model(1.0f);
			model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 view(1.0f);
			view = glm::lookAt(translation, glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 projection;
			projection = glm::perspective(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
			glm::mat4 transform = projection * view * model;
			shader.SetUniformMatrix4f("u_mvp", transform);

			//gl render
			//render.Renderprocess(va, ib, shader);



			//set imgui window
			{
				ImGui::SliderFloat3("translation", &translation[0], -30.0f, 30.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			ImGui::ShowDemoWindow();

			//imgui render
			imgui.render();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		imgui.clear();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
#endif
