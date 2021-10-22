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

int main(void)
{
	GLFWwindow* window = CreateWindow(5);
	assert(window != nullptr);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "error" << std::endl;
	}

	float cubeVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	//scope 方便释放资源
	{
		VertexArray cube_va;
		VertexBuffer cube_vb(cubeVertices, 5 * 36 * sizeof(float));
		VertexBufferLayout cube_layout;
		//将属性按顺序加入
		cube_layout.Push<float>(3);   //positon
		cube_layout.Push<float>(2);   //texture
		cube_va.AddBuffer(cube_vb, cube_layout);

		VertexArray plane_va;
		VertexBuffer plane_vb(planeVertices, 5 * 6 * sizeof(float));
		VertexBufferLayout plane_layout;
		//将属性按顺序加入
		plane_layout.Push<float>(3);   //positon
		plane_layout.Push<float>(2);   //texture
		plane_va.AddBuffer(plane_vb, plane_layout);

		Texture plane_texture("../res/image/metal.png");     //plane
		Texture cube_texture("../res/image/marble.jpg");    //continer

		/*启用模板测试*/
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		Shader shader("../res/shaders/Basics.shader");
		shader.UnBind();
		cube_vb.UnBind();
		cube_va.UnBind();
		plane_vb.UnBind();
		plane_va.UnBind();

		imguiCfg imgui(window);
		Render render;

		glm::vec3 camera = glm::vec3(0.0f, 1.0f, -5.0f);
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{

			GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

			imgui.start();

			shader.Bind();
			/*MVP*/
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::lookAt(camera, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
			glm::mat4 transform = projection * view * model;
			shader.SetUniformMatrix4f("u_mvp", transform);

			//plane
			glStencilMask(0x00);
			render.setFaceNum(6);
			plane_texture.Bind(0);
			shader.SetUniformi("texSampler0", 0);
			shader.SetUniformi("outline", 2);
			render.Renderprocess(plane_va, IndexBuffer(nullptr, 0), shader, DrawType::ARRAY);

			/*first step*/
			//模板开启写入，写入值用参考值替换
			glStencilMask(0xFF);
			//开启模板测试,cube的所有片元都通过
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			//cube1
			model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
			transform = projection * view * model;
			shader.SetUniformMatrix4f("u_mvp", transform);

			render.setFaceNum(36);
			cube_texture.Bind(0);
			shader.SetUniformi("texSampler0", 0);
			shader.SetUniformi("outline", 2);
			render.Renderprocess(cube_va, IndexBuffer(nullptr, 0), shader, DrawType::ARRAY);

			/*second step*/
			//模板禁止写入，开启模板测试
			glStencilMask(0x00);
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
			transform = projection * view * model;
			shader.SetUniformMatrix4f("u_mvp", transform);

			render.setFaceNum(36);
			cube_texture.Bind(0);
			shader.SetUniformi("texSampler0", 0);
			shader.SetUniformi("outline", 1);
			render.Renderprocess(cube_va, IndexBuffer(nullptr, 0), shader, DrawType::ARRAY);


			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
			//set imgui window
			{
				ImGui::SliderFloat3("camera", &camera[0], -30.0f, 30.0f);
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