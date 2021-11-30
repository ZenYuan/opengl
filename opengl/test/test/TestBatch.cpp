#include "TestBatch.h"

namespace test
{
#if 0
	
	TestBatch::TestBatch()
	{
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		//保存vertex Attribute,无需每次渲染切换layout;
		m_va = std::make_unique<VertexArray>();
		m_vb = std::make_unique<VertexBuffer>(vertices, 4 * 4 * sizeof(float), GL_STATIC_DRAW);
		
		VertexBufferLayout layout;
		layout.Push<float>(2);   //positon
		layout.Push<float>(2);   //texture

		m_va->AddBuffer(*m_vb, layout);

		m_ib = std::make_unique<IndexBuffer>(indices, 6, GL_STATIC_DRAW);
		m_shader = std::make_unique<Shader>("res/shaders/Basics.shader");

		

		m_TexArray["face"] = std::make_unique<Texture>("res/image/awesomeface.png");
		m_TexArray["kille"] = std::make_unique<Texture>("res/image/killeroo-simple.jpg");
	}

	void TestBatch::OnUpdate(float deltaTime)
	{

	}

	void TestBatch::OnRender()
	{
		glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, 1.0f, -1.0f);

		m_shader->Bind();
		m_TexArray["face"]->Bind(0);
		m_shader->SetUniformi("texSampler0", 0);
		m_TexArray["kille"]->Bind(1);
		m_shader->SetUniformi("texSampler1", 1);
		
		m_shader->SetUniformMatrix4f("u_mvp", proj);

		Render::Renderprocess(*m_va, *m_ib, *m_shader);
	}

	void TestBatch::OnImGuiRender()
	{
	}
#endif
}
