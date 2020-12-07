#ifndef EXAMPLE_LAYER_H
#define EXAMPLE_LAYER_H

#include <Jass.h>
#include <imgui.h>

// EXTREMELY TEMPORARY
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Jass::Layer {

public:

	ExampleLayer() :
		Layer("Example"), m_cameraController(1280.0f / 720.0f, true)
	{
		//RendererAPITest();
		RenderColorSquareTest();
		RenderTexSquareTest();
	}

	void OnUpdate(Jass::Timestep ts) override
	{
		Jass::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
		Jass::RenderCommand::Clear();

		//Jass::JMat4 transformation;
		//MoveTriangle(transformation, ts);

		m_cameraController.OnUpdate(ts);

		// Temporary
		std::dynamic_pointer_cast<Jass::OpenGLShader>(m_flatColorShader)->Bind();
		std::dynamic_pointer_cast<Jass::OpenGLShader>(m_flatColorShader)->UploadUniformFloat4("u_color", m_squareColor);

		Jass::Renderer::BeginScene(m_cameraController.GetCamera());
		Jass::Renderer::Submit(m_flatColorShader, m_squareVertexArray, Jass::Scale(Jass::JMat4(0.1f), Jass::JVec3(1.1f)));
		m_texture2D->Bind();
		Jass::Renderer::Submit(m_shaderLibrary.GetShader("TextureShader"), m_texSquareVertexArray);
		m_textureAlpha2D->Bind();
		Jass::Renderer::Submit(m_shaderLibrary.GetShader("TextureShader"), m_texSquareVertexArray);
		//Jass::Renderer::Submit(m_shader, m_vertexArray, transformation);
		Jass::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Color", Jass::GetPtr(m_squareColor));
		ImGui::End();
	}

	void OnEvent(Jass::Event& e) override
	{
		m_cameraController.OnEvent(e);
	}

private:
	Jass::OrthographicCameraController m_cameraController;

	Jass::ShaderLibrary m_shaderLibrary;

	Jass::Ref<Jass::VertexArray> m_vertexArray;
	Jass::Ref<Jass::Shader> m_shader;

	Jass::Ref<Jass::VertexArray> m_squareVertexArray;
	Jass::Ref<Jass::Shader> m_flatColorShader;
	Jass::JVec4 m_squareColor = Jass::JVec4(0.2f, 0.3f, 0.8f, 1.0f);

	Jass::Ref<Jass::Texture2D> m_textureAlpha2D;
	Jass::Ref<Jass::Texture2D> m_texture2D;
	Jass::Ref<Jass::VertexArray> m_texSquareVertexArray;

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

		m_shader = Jass::Shader::Create("TriangleShader", vertexShader, fragmentShader);

		m_vertexArray = Jass::VertexArray::Create();

		auto vertexBuffer = Jass::VertexBuffer::Create({ positions,sizeof(positions),Jass::DataUsage::StaticDraw });

		Jass::BufferLayout layout = {
			{Jass::ShaderDataType::Float3, "position" },
			{Jass::ShaderDataType::Float4, "v_color"}
		};
		vertexBuffer->SetLayout(layout);

		m_vertexArray->AddVertexBuffer(vertexBuffer);

		auto indexBuffer = Jass::IndexBuffer::Create({ indices,3,Jass::DataUsage::StaticDraw });

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

		m_flatColorShader = Jass::Shader::Create("FlatColorShader", vertexShader, fragmentShader);

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

		m_squareVertexArray = Jass::VertexArray::Create();

		auto vertexBuffer = Jass::VertexBuffer::Create({ positions,sizeof(positions),Jass::DataUsage::StaticDraw });
		vertexBuffer->SetLayout({
			Jass::BufferElement(Jass::ShaderDataType::Float3,"position")
			});

		m_squareVertexArray->AddVertexBuffer(vertexBuffer);

		auto indexBuffer = Jass::IndexBuffer::Create({ indices,6,Jass::DataUsage::StaticDraw });

		m_squareVertexArray->SetIndexBuffer(indexBuffer);
	}

	void RenderTexSquareTest()
	{
		auto texShader = m_shaderLibrary.Load("assets/shaders/TextureShader.glsl");

		m_texture2D = Jass::Texture2D::Create("assets/textures/Checkerboard.png");
		m_textureAlpha2D = Jass::Texture2D::Create("assets/textures/Appricot.png");

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

		m_texSquareVertexArray = Jass::VertexArray::Create();

		auto vertexBuffer = Jass::VertexBuffer::Create({ positions,sizeof(positions),Jass::DataUsage::StaticDraw });
		vertexBuffer->SetLayout({
			Jass::BufferElement(Jass::ShaderDataType::Float3,"position"),
			Jass::BufferElement(Jass::ShaderDataType::Float2,"texCoords")
			});

		m_texSquareVertexArray->AddVertexBuffer(vertexBuffer);

		auto indexBuffer = Jass::IndexBuffer::Create({ indices,6,Jass::DataUsage::StaticDraw });

		m_texSquareVertexArray->SetIndexBuffer(indexBuffer);

		std::dynamic_pointer_cast<Jass::OpenGLShader>(texShader)->Bind();
		std::dynamic_pointer_cast<Jass::OpenGLShader>(texShader)->UploadUniformInt("u_texture", 0);
	}

	void MoveTriangle(Jass::JMat4& transformation, Jass::Timestep ts)
	{
		static Jass::JVec3 trianglePosition(0.0f);
		float triangleSpeed = 3.0f;

		if (Jass::Input::IsKeyPressed(JASS_KEY_L))
			trianglePosition.x += triangleSpeed * ts;
		else if (Jass::Input::IsKeyPressed(JASS_KEY_J))
			trianglePosition.x -= triangleSpeed * ts;

		if (Jass::Input::IsKeyPressed(JASS_KEY_I))
			trianglePosition.y += triangleSpeed * ts;
		else if (Jass::Input::IsKeyPressed(JASS_KEY_K))
			trianglePosition.y -= triangleSpeed * ts;

		transformation = Jass::Translate(Jass::JMat4(1.0f), trianglePosition);
	}

};

#endif // !EXAMPLE_LAYER_H

