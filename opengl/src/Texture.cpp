#include "common.h"
#include "Texture.h"
#include "Render.h"
#include "stb_image.h"

Texture::Texture(const std::string& imagePath):
	m_RenderId(0), m_Width(0), m_Height(0), m_BPP(0), m_LocalImage(nullptr)
{
	/*read image*/
	stbi_set_flip_vertically_on_load(true);   //设置反转，opengl的bottom是（0，0）
	m_LocalImage = stbi_load(imagePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	if (!m_LocalImage)
	{
		ASSERT(false);
	}
		
	/*set Texture param*/
	GLCall(glGenTextures(1, &m_RenderId));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderId));

	/*过滤方式*/
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	/*环绕方式*/
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalImage));
	//glGenerateMipmap(GL_TEXTURE_2D);

	if (m_LocalImage)
	{
		stbi_image_free(m_LocalImage);
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RenderId));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderId));
}

void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
