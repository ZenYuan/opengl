#include "TestClearColor.h"
#include "GL/glew.h"
#include "imgui.h"

namespace test
{
	TestClearColor::TestClearColor():
		m_ClearColor { 1.0, 1.0, 0.0, 1.0 }
	{
	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{
	}

	void TestClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[2]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("clear color", m_ClearColor);
	}
}