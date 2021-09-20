#include "TestCube.h"


#include "Renderer.h"
#include "imgui/imgui.h"



#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace test {
    TestCube::TestCube()
        : m_Proj(glm::perspective(45.0f, 1.0f * 800 / 600, 0.1f, 10.0f)),
        m_View(glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0))),
        m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0), m_xRot(false), m_yRot(false), m_zRot(false)
        
	{

		//triangle position verticies
        GLfloat positions[] = {
            // front
            -1.0, -1.0,  1.0,
             1.0, -1.0,  1.0,
             1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
            // back
            -1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0
        };

        GLfloat colorsBuffer[] = {
            // front colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
            // back colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
        };


        unsigned int indices[] = {
                // front
                0, 1, 2,
                2, 3, 0,
                // right
                1, 5, 6,
                6, 2, 1,
                // back
                7, 6, 5,
                5, 4, 7,
                // left
                4, 0, 3,
                3, 7, 4,
                // bottom
                4, 5, 1,
                1, 0, 4,
                // top
                3, 2, 6,
                6, 7, 3
        };

     
        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));
        m_ColorsBuffer = std::make_unique<VertexBuffer>(colorsBuffer, sizeof(colorsBuffer));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        
        
 
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_VAO->AddBuffer(*m_ColorsBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices));


        m_Shader = std::make_unique<Shader>("res/shaders/Cube.shader");
        m_Shader->Bind();
        m_attribute_coord3d = m_Shader->GetAttribLoc("coord3d");
        m_attribute_v_color = m_Shader->GetAttribLoc("v_color");
        
        
        //   print out shader info. 

        //   std::cout << "\nVERTEX" << std::endl;
        //   std::cout << source.VertexSource << std::endl;
        //   std::cout << "FRAGMENT" << std::endl;
        //   std::cout << source.FragmentSource << std::endl;

	}

    TestCube::~TestCube()
	{
	}

	void TestCube::OnUpdate(float deltaTime)
	{
        m_angle += 0.5f;
        if (m_angle >= 360) m_angle = 0;

        glm::vec3 axis_y(m_xRot, m_yRot, m_zRot);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));

        if(m_xRot || m_yRot || m_zRot)
            model = glm::rotate(model, glm::radians(m_angle), axis_y);

        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);

	}

	void TestCube::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;
        
        
        glEnableVertexAttribArray(m_attribute_coord3d);
        // Describe our vertices array to OpenGL (it can't guess its format automatically)
        m_VertexBuffer->Bind();
        glVertexAttribPointer(
            m_attribute_coord3d, // attribute
            3,                 // number of elements per vertex, here (x,y,z)
            GL_FLOAT,          // the type of each element
            GL_FALSE,          // take our values as-is
            0,                 // no extra data between each position
            0                  // offset of first element
        );


        glEnableVertexAttribArray(m_attribute_v_color);
        m_ColorsBuffer->Bind();
        glVertexAttribPointer(
            m_attribute_v_color, // attribute
            3,                 // number of elements per vertex, here (R,G,B)
            GL_FLOAT,          // the type of each element
            GL_FALSE,          // take our values as-is
            0,                 // no extra data between each position
            0                  // offset of first element
        );

        m_IndexBuffer->Bind();


        
        
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

        glDisableVertexAttribArray(m_attribute_coord3d);
        glDisableVertexAttribArray(m_attribute_v_color);
        
    }

	void TestCube::OnImGuiRender()
	{
        ImGui::Checkbox("x-axis rotation", &m_xRot);
        ImGui::Checkbox("y-axis rotation", &m_yRot);
        ImGui::Checkbox("z-axis rotation", &m_zRot);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}