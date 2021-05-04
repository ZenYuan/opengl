#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError(); \
					x; \
					ASSERT(GLLogCall(#x, __LINE__))

/*在获取任意错误码前清除之前的错误码*/
static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL error]"<< "(" <<error << ")" <<" "
			<<"func:"<<function<<" "<<"line:"<<line<<std::endl;
		return false;
	}
	return true;
}

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

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
		GLCall(glUniform4f(location, rand()%10/10.0f, 0.2, 0.3, 0.1));
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}