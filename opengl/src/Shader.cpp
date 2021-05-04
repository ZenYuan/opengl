#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Shader.h"
#include "Render.h"

Shader::Shader(const std::string& filepath)
{
	ShaderSource source = ParseShader(filepath.c_str());
	m_RenderId = CreateShaderProgream(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{

}


/*get shader source from file*/
ShaderSource Shader::ParseShader(const std::string& filePath)
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

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompilerShader(unsigned int type, const std::string& shaderSource)
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
		char* log = (char*)alloca(sizeof(char) * length);
		glGetShaderInfoLog(id, length, nullptr, log);
		std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader error:";
		std::cout << log << std::endl;
		glDeleteShader(id);
	}
	return id;
}


unsigned int Shader::CreateShaderProgream(const std::string& VertexSource, const std::string& FrgamentShader)
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


void Shader::Bind() const
{
	GLCall(glUseProgram(m_RenderId));
}

void Shader::UnBind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, glm::vec4& vec)
{
	GLCall(glUniform4f(GetUniformLocation(name), vec.r, vec.g, vec.b, vec.a));
}

int Shader::GetUniformLocation(const std::string& name)
{
	GLCall(int location = glGetUniformLocation(m_RenderId, name.c_str()));

	if (-1 == location)
	{
		std::cout << "uniform:" << name << "not exist!" << std::endl;
	}
	return location;
}
