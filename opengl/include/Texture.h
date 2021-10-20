#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& imagePath);
	~Texture();

	/*opengl support 8/16/32 texture slot, default set zero*/
	void Bind(unsigned int slot = 0) const;
	void UnBind() const;
private:
	unsigned int m_RenderId;
	int m_Width;
	int m_Height;
	unsigned char* m_LocalImage;
	int m_BPP;
};