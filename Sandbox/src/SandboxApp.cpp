#include "Jass.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

// TEMPORARY
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Jass::Layer {

public:
	
	ExampleLayer() :
		Layer("Example"), m_camera({ -1.6f,1.6f,-0.9f,0.9f })
	{
		//RendererAPITest();
		RenderColorSquareTest();
		RenderTexSquareTest();
	}

	void OnUpdate(Jass::Timestep ts) override
	{
		Jass::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
		Jass::RenderCommand::Clear();

		MoveCameraInput(ts);

		//glm::mat4 transformation;
		//MoveTriangle(transformation, ts);

		// Temporary
		std::dynamic_pointer_cast<Jass::OpenGLShader>(m_flatColorShader)->Bind();
		std::dynamic_pointer_cast<Jass::OpenGLShader>(m_flatColorShader)->UploadUniformFloat4("u_color", m_squareColor);

		Jass::Renderer::BeginScene(m_camera);
		Jass::Renderer::Submit(m_flatColorShader, m_squareVertexArray, glm::scale(glm::mat4(0.1f),glm::vec3(1.1f)));
		m_texture2D->Bind();
		Jass::Renderer::Submit(m_texShader, m_texSquareVertexArray);
		//Jass::Renderer::Submit(m_shader, m_vertexArray, transformation);
		Jass::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Color", glm::value_ptr(m_squareColor));
		ImGui::End();
	}

	void OnEvent(Jass::Event& e) override
	{
		//Jass::EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<Jass::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
	}

	void MoveCameraInput(Jass::Timestep ts)
	{
		auto cameraPosition = m_camera.GetPosition();
		auto cameraRotation = m_camera.GetRotation();
		float cameraMoveSpeed = 3.0f;
		float cameraRotationSpeed = 100.0f;

		if (Jass::Input::IsKeyPressed(JASS_KEY_UP))
			cameraPosition.y += cameraMoveSpeed * ts;
		else if (Jass::Input::IsKeyPressed(JASS_KEY_DOWN))
			cameraPosition.y -= cameraMoveSpeed * ts;

		if (Jass::Input::IsKeyPressed(JASS_KEY_RIGHT))
			cameraPosition.x += cameraMoveSpeed * ts;
		else if (Jass::Input::IsKeyPressed(JASS_KEY_LEFT))
			cameraPosition.x -= cameraMoveSpeed * ts;

		if (Jass::Input::IsKeyPressed(JASS_KEY_A))
			cameraRotation.z += cameraRotationSpeed * ts;
		else if (Jass::Input::IsKeyPressed(JASS_KEY_D))
			cameraRotation.z -= cameraRotationSpeed * ts;

		m_camera.SetPosition(cameraPosition);
		m_camera.SetRotation(cameraRotation);
	}

	bool OnKeyPressed(Jass::KeyPressedEvent& e)
	{	
		MoveCamera(e.GetKeyCode());
		return true;
	}

private:
	Jass::OrthographicCamera m_camera;

	Jass::Ref<Jass::VertexArray> m_vertexArray;
	Jass::Ref<Jass::Shader> m_shader;
	
	Jass::Ref<Jass::VertexArray> m_squareVertexArray;
	Jass::Ref<Jass::Shader> m_flatColorShader;
	glm::vec4 m_squareColor = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);

	Jass::Ref<Jass::Texture2D> m_texture2D;
	Jass::Ref<Jass::VertexArray> m_texSquareVertexArray;
	Jass::Ref<Jass::Shader> m_texShader;

	void RendererAPITest()
	{
		float positions[]{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.1f, 0.4f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.1f, 0.2f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.2f, 0.5f, 0.5f, 1.0f
		};

		unsigned int indices[]{
			0, 1, 2
		};

		std::string vertexShader = R"(
			#version 330 core

			layout(location = 0) in vec4 position;
			layout(location = 1) in vec4 v_color;
	
			out vec4 color;
			uniform mat4 u_viewProjection;
			uniform mat4 u_transformation;

			void main()
			{
				gl_Position = u_viewProjection * u_transformation * position;
				color = v_color;
			}
			
		)";

		std::string fragmentShader = R"(
			#version 330 core
			
			layout(location = 0) out vec4 o_color;
				
			in vec4 color;

			void main()
			{
				o_color = color;
			}
			
		)";

		m_shader.reset(Jass::Shader::Create(vertexShader, fragmentShader));

		m_vertexArray.reset(Jass::VertexArray::Create());

		std::shared_ptr<Jass::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Jass::VertexBuffer::Create({ positions,sizeof(positions),Jass::DataUsage::StaticDraw }));

		Jass::BufferLayout layout = {
			{Jass::ShaderDataType::Float3, "position" },
			{Jass::ShaderDataType::Float4, "v_color"}
		};
		vertexBuffer->SetLayout(layout);

		m_vertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<Jass::IndexBuffer> indexBuffer;
		indexBuffer.reset(Jass::IndexBuffer::Create({ indices,3,Jass::DataUsage::StaticDraw }));

		m_vertexArray->SetIndexBuffer(indexBuffer);
	}

	void RenderColorSquareTest()
	{
		std::string vertexShader = R"(
			#version 330 core

			layout(location = 0) in vec4 position;
	
			out vec4 color;
			uniform mat4 u_viewProjection;
			uniform mat4 u_transformation;
			uniform vec4 u_color;

			void main()
			{
				gl_Position = u_viewProjection * u_transformation * position;
				color = u_color;
			}
			
		)";

		std::string fragmentShader = R"(
			#version 330 core
			
			layout(location = 0) out vec4 o_color;
				
			in vec4 color;

			void main()
			{
				o_color = color;
			}
			
		)";

		m_flatColorShader.reset(Jass::Shader::Create(vertexShader, fragmentShader));

		float positions[] = {
			-0.75f, -0.75f, 0.0f,	// 0
			0.75f, -0.75f, 0.0f,	// 1
			0.75f, 0.75f, 0.0f,		// 2
			-0.75f, 0.75f, 0.0f		// 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_squareVertexArray.reset(Jass::VertexArray::Create());

		std::shared_ptr<Jass::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Jass::VertexBuffer::Create({ positions,sizeof(positions),Jass::DataUsage::StaticDraw }));
		vertexBuffer->SetLayout({
			Jass::BufferElement(Jass::ShaderDataType::Float3,"position")
			});

		m_squareVertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<Jass::IndexBuffer> indexBuffer;
		indexBuffer.reset(Jass::IndexBuffer::Create({ indices,6,Jass::DataUsage::StaticDraw }));

		m_squareVertexArray->SetIndexBuffer(indexBuffer);
	}

	void RenderTexSquareTest()
	{
		std::string vertexShader = R"(
			#version 330 core

			layout(location = 0) in vec4 position;
			layout(location = 1) in vec2 texCoords;

			out vec2 o_texCoords;
	
			uniform mat4 u_viewProjection;
			uniform mat4 u_transformation;

			void main()
			{
				gl_Position = u_viewProjection * u_transformation * position;
				o_texCoords = texCoords;
			}
			
		)";

		std::string fragmentShader = R"(
			#version 330 core
			
			layout(location = 0) out vec4 o_color;
				
			in vec2 o_texCoords;

			uniform sampler2D u_texture;

			void main()
			{
				o_color = texture(u_texture, o_texCoords);
			}
			
		)";

		m_texShader.reset(Jass::Shader::Create(vertexShader, fragmentShader));

		m_texture2D = Jass::Texture2D::Create("assets/textures/Checkerboard.png");

		float positions[] = {
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,	// 0
			0.75f, -0.75f, 0.0f, 1.0f, 0.0f,	// 1
			0.75f, 0.75f, 0.0f, 1.0f, 1.0f,		// 2
			-0.75f, 0.75f, 0.0f, 0.0f, 1.0f		// 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_texSquareVertexArray.reset(Jass::VertexArray::Create());

		std::shared_ptr<Jass::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Jass::VertexBuffer::Create({ positions,sizeof(positions),Jass::DataUsage::StaticDraw }));
		vertexBuffer->SetLayout({
			Jass::BufferElement(Jass::ShaderDataType::Float3,"position"),
			Jass::BufferElement(Jass::ShaderDataType::Float2,"texCoords")
			});

		m_texSquareVertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<Jass::IndexBuffer> indexBuffer;
		indexBuffer.reset(Jass::IndexBuffer::Create({ indices,6,Jass::DataUsage::StaticDraw }));

		m_texSquareVertexArray->SetIndexBuffer(indexBuffer);

		std::dynamic_pointer_cast<Jass::OpenGLShader>(m_texShader)->Bind();
		std::dynamic_pointer_cast<Jass::OpenGLShader>(m_texShader)->UploadUniformInt("u_texture", 0);
	}

	void MoveCamera(int keyCode)
	{
		auto cameraPosition = m_camera.GetPosition();
		switch (keyCode)
		{
			case JASS_KEY_LEFT:
				m_camera.SetPosition(cameraPosition + glm::vec3(-0.1f, 0.0f, 0.0f));
				break;
			case JASS_KEY_RIGHT:
				m_camera.SetPosition(cameraPosition + glm::vec3(0.1f, 0.0f, 0.0f));
				break;
			case JASS_KEY_UP:
				m_camera.SetPosition(cameraPosition + glm::vec3(0.0f, 0.1f, 0.0f));
				break;
			case JASS_KEY_DOWN:
				m_camera.SetPosition(cameraPosition + glm::vec3(0.0f, -0.1f, 0.0f));
				break;
		}
	}

	void MoveTriangle(glm::mat4& transformation, Jass::Timestep ts)
	{
		static glm::vec3 trianglePosition(0.0f);
		float triangleSpeed = 3.0f;

		if (Jass::Input::IsKeyPressed(JASS_KEY_L))
			trianglePosition.x += triangleSpeed * ts;
		else if (Jass::Input::IsKeyPressed(JASS_KEY_J))
			trianglePosition.x -= triangleSpeed * ts;

		if (Jass::Input::IsKeyPressed(JASS_KEY_I))
			trianglePosition.y += triangleSpeed * ts;
		else if (Jass::Input::IsKeyPressed(JASS_KEY_K))
			trianglePosition.y -= triangleSpeed * ts;

		transformation = glm::translate(glm::mat4(1.0f), trianglePosition);
	}

};

class Sandbox : public Jass::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}

};

Jass::Application* Jass::CreateApplication() {
	return new Sandbox();
}