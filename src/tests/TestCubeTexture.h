#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>


namespace test {

	class TestCubeTexture : public Test
	{
	public:
		TestCubeTexture();
		~TestCubeTexture();


		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexBuffer> m_TexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		GLuint m_program, m_textureID;
		GLint m_attribute_coord3d, m_attribute_texcoord;
		GLint m_uniform_mvp, m_uniform_cubetexture;
		float m_angle;

		bool m_xRot, m_yRot, m_zRot, fly;
		

		glm::mat4 m_Proj, m_View;

		glm::vec3 m_TranslationA, m_TranslationB;
		
	};
}