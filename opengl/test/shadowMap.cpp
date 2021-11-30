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
//#define debug

int main6(void)
{
	GLFWwindow* window = CreateWindow(5);
	assert(window != nullptr);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "error" << std::endl;
	}

	float cubeVertices[] = {
		// back face
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
		// front face
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		// left face
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		// right face
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
		// bottom face
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		// top face
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
	};

	float planeVertices[] = {
		// positions            // normals         // texcoords
		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
		 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
	};

#ifdef debug
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
	};
#endif

	//scope 方便释放资源
	{
		VertexArray cube_va;
		VertexBuffer cube_vb(cubeVertices, 8 * 36 * sizeof(float));
		VertexBufferLayout cube_layout;
		//将属性按顺序加入
		cube_layout.Push<float>(3);   //positon
		cube_layout.Push<float>(3);   //normal
		cube_layout.Push<float>(2);   //texture
		cube_va.AddBuffer(cube_vb, cube_layout);

		VertexArray plane_va;
		VertexBuffer plane_vb(planeVertices, 8 * 6 * sizeof(float));
		VertexBufferLayout plane_layout;
		//将属性按顺序加入
		plane_layout.Push<float>(3);   //positon
		plane_layout.Push<float>(3);   //noraml
		plane_layout.Push<float>(2);   //texture
		plane_va.AddBuffer(plane_vb, plane_layout);

#ifdef debug
		VertexArray quad_va;
		VertexBuffer quad_vb(quadVertices, 4 * 6 * sizeof(float));
		VertexBufferLayout quad_layout;
		quad_layout.Push<float>(2);
		quad_layout.Push<float>(2);
		quad_va.AddBuffer(quad_vb, quad_layout);

		quad_vb.UnBind();
		quad_va.UnBind();

		Shader debugshader("../res/shaders/framebuffer2.shader");
		debugshader.UnBind();
#endif

		Texture plane_texture("../res/image/wood.png");     //plane
		Texture cube_texture("../res/image/container.jpg");    //continer

		Shader shader_depthmap("../res/shaders/shadowMap/depthMap.shader");
		Shader sceneshader("../res/shaders/shadowMap/shadow.shader");
		shader_depthmap.UnBind();
		sceneshader.UnBind();
		cube_vb.UnBind();
		cube_va.UnBind();
		plane_vb.UnBind();
		plane_va.UnBind();

		//generate shadowmap FBO
		unsigned int shadowMapFbo = -1;
		GLCall(glGenFramebuffers(1, &shadowMapFbo));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFbo));

		const unsigned int shadowwidth = 1920, shadowheight = 1080;
		unsigned int depthMapTex = -1;
		GLCall(glGenTextures(1, &depthMapTex));
		GLCall(glBindTexture(GL_TEXTURE_2D, depthMapTex));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowwidth, shadowheight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapTex, 0));

		//只需要深度缓存，不需要渲染到colorbuffer;需要显示关闭
		GLCall(glDrawBuffer(GL_NONE));
		GLCall(glReadBuffer(GL_NONE));

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "not complete framebuffer" << std::endl;
			return -1;
		}
		
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

		imguiCfg imgui(window);
		Render render;

		glm::vec3 light = glm::vec3(-2.0f, 4.0f, -1.0f);
		glm::vec3 eye = glm::vec3(0.0f, 3.0f, 5.0f);
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			imgui.start();

			/*lightVP*/
			glm::mat4 lightview = glm::lookAt(light, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 ortho = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 100.0f);
			glm::mat4 lightVP = ortho * lightview;

			shader_depthmap.Bind();
			shader_depthmap.SetUniformMatrix4f("light_vp", lightVP);
			
			GLCall(glViewport(0, 0, shadowwidth, shadowheight));
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFbo));
			GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			glEnable(GL_DEPTH_TEST);
			//scene
			{
				// floor
				glm::mat4 model = glm::mat4(1.0f);
				shader_depthmap.SetUniformMatrix4f("model", model);
				render.setFaceNum(6);
				render.Renderprocess(plane_va, IndexBuffer(nullptr, 0), shader_depthmap, DrawType::ARRAY);

				// cubes
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
				model = glm::scale(model, glm::vec3(0.5f));
				shader_depthmap.SetUniformMatrix4f("model", model);
				render.setFaceNum(36);
				render.Renderprocess(cube_va, IndexBuffer(nullptr, 0), shader_depthmap, DrawType::ARRAY);
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
				model = glm::scale(model, glm::vec3(0.5f));
				shader_depthmap.SetUniformMatrix4f("model", model);
				render.setFaceNum(36);
				render.Renderprocess(cube_va, IndexBuffer(nullptr, 0), shader_depthmap, DrawType::ARRAY);
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
				model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
				model = glm::scale(model, glm::vec3(0.25));
				shader_depthmap.SetUniformMatrix4f("model", model);
				render.setFaceNum(36);
				render.Renderprocess(cube_va, IndexBuffer(nullptr, 0), shader_depthmap, DrawType::ARRAY);
			}
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

			/*vp*/
			GLCall(glViewport(0, 0, 800, 600));
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glm::mat4 view = glm::lookAt(eye, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 project = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);

			sceneshader.Bind();
			sceneshader.SetUniformMatrix4f("view", view);
			sceneshader.SetUniformMatrix4f("projection", project);
			sceneshader.SetUniformMatrix4f("light_vp", lightVP);
			sceneshader.SetUniform3f("lightpos", light);
			sceneshader.SetUniform3f("eyepos", eye);
			sceneshader.SetUniformi("sceneTexSampler", 1);
			sceneshader.SetUniformi("depthTexSampler", 0);

			GLCall(glActiveTexture(GL_TEXTURE0));
			GLCall(glBindTexture(GL_TEXTURE_2D, depthMapTex));


			//scene
			{
				// floor
				glm::mat4 model = glm::mat4(1.0f);
				sceneshader.SetUniformMatrix4f("model", model);
				plane_texture.Bind(1);
				render.setFaceNum(6);
				render.Renderprocess(plane_va, IndexBuffer(nullptr, 0), sceneshader, DrawType::ARRAY);

				// cubes
				cube_texture.Bind(1);
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
				model = glm::scale(model, glm::vec3(0.5f));
				sceneshader.SetUniformMatrix4f("model", model);
				render.setFaceNum(36);
				render.Renderprocess(cube_va, IndexBuffer(nullptr, 0), sceneshader, DrawType::ARRAY);
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
				model = glm::scale(model, glm::vec3(0.5f));
				sceneshader.SetUniformMatrix4f("model", model);
				render.setFaceNum(36);
				render.Renderprocess(cube_va, IndexBuffer(nullptr, 0), sceneshader, DrawType::ARRAY);
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
				model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
				model = glm::scale(model, glm::vec3(0.25));
				sceneshader.SetUniformMatrix4f("model", model);
				render.setFaceNum(36);
				render.Renderprocess(cube_va, IndexBuffer(nullptr, 0), sceneshader, DrawType::ARRAY);
			}



#ifdef debug
			GLCall(glViewport(0, 0, 800, 600));
			GLCall(glDisable(GL_DEPTH_TEST));
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			debugshader.Bind();
			quad_va.Bind();
			GLCall(glActiveTexture(GL_TEXTURE0));
			GLCall(glBindTexture(GL_TEXTURE_2D, depthMapTex));
			debugshader.SetUniformi("texsample", 0);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
#endif
			//set imgui window
			{
				ImGui::SliderFloat3("light", &light[0], -30.0f, 30.0f);
				ImGui::SliderFloat3("eye", &eye[0], -30.0f, 30.0f);
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