#include "Test.h"
#include "imgui.h"

namespace test
{
	TestMenu::TestMenu(Test*& currentTest):
		m_CurrentTest(currentTest)
	{
		m_CurrentTest = this;
	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_CurrentTest = test.second();
			}
		}
	}
}