#pragma once

#include <GLFW/glfw3.h>

class imguiCfg
{
public:
	imguiCfg(GLFWwindow* window) { init(window); }
	void start();
	void setImgui();
	void render();
	void clear();
private:
	void init(GLFWwindow* window);
};