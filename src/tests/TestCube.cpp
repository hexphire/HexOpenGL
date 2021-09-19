#include "TestCube.h"


#include "Renderer.h"
#include "imgui/imgui.h"



#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {
    TestCube::TestCube()
        : m_Proj(glm::perspective(45.0f, 1.0f * 800 / 600, 0.1f, 10.0f)),
        m_View(glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0))),
        m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
        
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
        layout.Push<float>(2);
        
        
        


        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_VAO->AddBuffer(*m_ColorsBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices));

        m_Shader = std::make_unique<Shader>("res/shaders/Cube.shader");
        m_Shader->Bind();

        m_program = m_Shader->getProgram();
        GLint link_ok = GL_FALSE;
        glLinkProgram(m_program);
        glGetProgramiv(m_program, GL_LINK_STATUS, &link_ok);
        if (!link_ok) {
            fprintf(stderr, "glLinkProgram:");
        }


        const char* attribute_name;
        attribute_name = "coord3d";
        m_attribute_coord3d = glGetAttribLocation(m_program, attribute_name);
        if (m_attribute_coord3d == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
        }

        attribute_name = "v_color";
        m_attribute_v_color = glGetAttribLocation(m_program, attribute_name);
        if (m_attribute_coord3d == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
        }
        const char* uniform_name;
        uniform_name = "u_MVP";
        m_uniform_mvp = glGetUniformLocation(m_program, uniform_name);
        if (m_uniform_mvp == -1) {
            fprintf(stderr, "Could not bind uniform %s\n", uniform_name);   
        }




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
	}

	void TestCube::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;

        glUseProgram(m_program);
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


        
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

        glDisableVertexAttribArray(m_attribute_coord3d);
        glDisableVertexAttribArray(m_attribute_v_color);
        
    }

	void TestCube::OnImGuiRender()
	{
       
	}
}