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

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
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

		VertexArray quad_va;
		VertexBuffer quad_vb(quadVertices, 4 * 6* sizeof(float));
		VertexBufferLayout quad_layout;
		quad_layout.Push<float>(2);
		quad_layout.Push<float>(2);
		quad_va.AddBuffer(quad_vb, quad_layout);

		Texture plane_texture("../res/image/metal.png");     //plane
		Texture cube_texture("../res/image/marble.jpg");    //continer

		Shader shader("../res/shaders/framebuffer.shader");
		Shader screen_shader("../res/shaders/framebuffer2.shader");
		shader.UnBind();
		screen_shader.UnBind();
		cube_vb.UnBind();
		cube_va.UnBind();
		plane_vb.UnBind();
		plane_va.UnBind();
		quad_vb.UnBind();
		quad_va.UnBind();

		//frameBuffer
		unsigned int framebuffer;
		GLCall(glGenFramebuffers(1, &framebuffer));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, framebuffer));

		//create color attachment texture
		unsigned int textureColorbuffer;
		GLCall(glGenTextures(1, &textureColorbuffer));
		GLCall(glBindTexture(GL_TEXTURE_2D, textureColorbuffer));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0));

		//renderbuffer object用于深度测试buffer
		//否则即使开启了深度测试，但是不存在depth——buffer，无法测试
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "not complete framebuffer" << std::endl;
		}
		
		//解绑FBO
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		imguiCfg imgui(window);
		Render render;


		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, -5.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
		glm::mat4 transform = projection * view * model;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			imgui.start();

//pass1
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, framebuffer));
			GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			GLCall(glEnable(GL_DEPTH_TEST));
			
			shader.Bind();
			shader.SetUniformMatrix4f("u_mvp", transform);

			//cube1
			cube_texture.Bind(0);
			shader.SetUniformi("texsample", 0);
			render.setFaceNum(36);
			render.Renderprocess(cube_va, IndexBuffer(nullptr, 0), shader, DrawType::ARRAY);

			//plane
			plane_texture.Bind(0);
			shader.SetUniformi("texsample", 0);
			render.setFaceNum(6);
			render.Renderprocess(plane_va, IndexBuffer(nullptr, 0), shader, DrawType::ARRAY);

//pass2
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			GLCall(glDisable(GL_DEPTH_TEST));
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			screen_shader.Bind();
			quad_va.Bind();
			GLCall(glActiveTexture(GL_TEXTURE0));
			GLCall(glBindTexture(GL_TEXTURE_2D, textureColorbuffer));
			screen_shader.SetUniformi("texsample", 0);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));

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