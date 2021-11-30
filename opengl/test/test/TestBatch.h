#pragma once
#include "Test.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include <map>
#include <string>

namespace test
{
#if 0
	class TestBatch : public Test
	{
	public:
		TestBatch();
		~TestBatch() {}

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::map<std::string, std::unique_ptr<Texture>> m_TexArray;
		std::unique_ptr<VertexArray> m_va;
		std::unique_ptr<VertexBuffer> m_vb;
		std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<Shader> m_shader;
	};
#endif
}
