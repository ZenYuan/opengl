#pragma once
#include "glm/vec4.hpp"
#include <string>

struct ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	/*set uniform*/
	void SetUniform4f(const std::string& name, glm::vec4& vec);
private:
	int GetUniformLocation(const std::string& name);
	unsigned int CreateShaderProgream(const std::string& VertexSource, const std::string& FrgamentShader);
	unsigned int CompilerShader(unsigned int type, const std::string& shaderSource);
	ShaderSource ParseShader(const std::string& filePath);
private:
	unsigned int m_RenderId;
};