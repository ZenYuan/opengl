#pragma once
#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"
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
	void SetUniform4f(const std::string& name, const glm::vec4& vec);
	void SetUniform3f(const std::string& name, const glm::vec3& vec);
	void SetUniformi(const std::string& name, int slot);
	void SetUniformMatrix4f(const std::string& name, glm::mat4& mat4);
private:
	int GetUniformLocation(const std::string& name);
	unsigned int CreateShaderProgream(const std::string& VertexSource, const std::string& FrgamentShader);
	unsigned int CompilerShader(unsigned int type, const std::string& shaderSource);
	ShaderSource ParseShader(const std::string& filePath);
private:
	unsigned int m_RenderId;
};