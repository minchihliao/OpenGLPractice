#include "TestTexture2D.h"

#include "Renderer.h"
#include "ImGui/imgui.h"

#include "glm/glm.hpp";
#include "glm/gtc/matrix_transform.hpp";


namespace test {
	TestTexture2D::TestTexture2D()
		:m_Proj(glm::ortho(0.f, 960.f, 0.f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
	{
		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f,
			50.0f, -50.0f, 1.0f, 0.0f,
			50.0f,  50.0f, 1.0f, 1.0f,
			-50.0f,  50.0f, 0.0f, 1.0f,

			50.0f, 100.0f, 0.0f, 0.0f,
			150.0f, 100.0f, 1.0f, 0.0f,
			150.0f, 200.0f, 1.0f, 1.0f,
			50.0f, 200.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 8 * 4 * sizeof(float));


		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


		m_Texture = std::make_unique<Texture>("res/textures/enemy.png");

		m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		m_Texture->Bind();




		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->SetUniformMat4F("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

		/*	{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
				glm::mat4 mvp = m_Proj * m_View * model;
				m_Shader->Bind();
				m_Shader->SetUniformMat4F("u_MVP", mvp);
				renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
			}*/

	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}

}