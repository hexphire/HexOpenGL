#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>


namespace test {

	class TestCube : public Test
	{
	public:
		TestCube();
		~TestCube();


		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexBuffer> m_ColorsBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		GLuint m_program;
		GLint m_attribute_coord3d, m_attribute_v_color;
		GLint m_uniform_mvp;
		float m_angle;

		bool m_xRot, m_yRot, m_zRot;
		

		glm::mat4 m_Proj, m_View;

		glm::vec3 m_TranslationA, m_TranslationB;
		
	};
}