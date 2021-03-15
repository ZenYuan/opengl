#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>


static unsigned int compilerShader(unsigned int type, const std::string& shaderSource)
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
	}
	return id;
}


static unsigned int CreateShaderProgream(const std::string& VertexSource, const std::string& FrgamentShader)
{
	unsigned int vs = compilerShader(GL_VERTEX_SHADER, VertexSource);
	unsigned int fs = compilerShader(GL_FRAGMENT_SHADER, FrgamentShader);

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

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "error" << std::endl;
	}

	float vertices[] =
	{
		-0.5f, -0.5f,
		0.0f , 0.5f,
		0.5f , -0.5f
	};

	const std::string vertexSource =
		"#version 330 core\n"
		" layout(location = 0) in vec4 position;\n"
		" void main()\n"
		"{\n"
		"gl_Position = position; \n"
		"}\n";

	const std::string frgamentSource =
		"#version 330 core\n"
		" out vec4 color;\n"
		" void main()\n"
		"{\n"
		" color = vec4(1.0, 0.0, 0.0, 1.0) \n"
		"}\n";




	unsigned int progream = CreateShaderProgream(vertexSource, frgamentSource);
	glUseProgram(progream);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}