#include "Jass.h"

class ExampleLayer : public Jass::Layer {

public:
	
	ExampleLayer() :
		Layer("Example"), m_camera({ -1.6f,1.6f,-0.9f,0.9f })
	{
		RendererAPITest();
	}

	void OnUpdate(Jass::Timestep ts) override
	{
		Jass::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
		Jass::RenderCommand::Clear();

		MoveCameraInput(ts);

		Jass::Renderer::BeginScene(m_camera);
		Jass::Renderer::Submit(m_shader, m_vertexArray);
		Jass::Renderer::EndScene();
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
	std::shared_ptr<Jass::VertexArray> m_vertexArray;
	std::shared_ptr<Jass::Shader> m_shader;

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
			uniform mat4 v_viewProjection;

			void main()
			{
				gl_Position = v_viewProjection * position;
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

		m_shader = std::make_shared<Jass::Shader>(vertexShader, fragmentShader);

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