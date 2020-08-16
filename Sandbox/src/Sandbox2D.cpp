#include "Sandbox2D.h"
#include <imgui.h>

// EXTREMELY TEMPORARY
#include <Platform/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D() :
	Layer("Sandbox2D"), m_cameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	FlatColorSquareTest();
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Jass::Timestep ts)
{
	m_cameraController.OnUpdate(ts);

	Jass::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
	Jass::RenderCommand::Clear();

	// Temporary
	std::dynamic_pointer_cast<Jass::OpenGLShader>(m_flatColorShader)->Bind();
	std::dynamic_pointer_cast<Jass::OpenGLShader>(m_flatColorShader)->UploadUniformFloat4("u_color", m_squareColor);

	Jass::Renderer::BeginScene(m_cameraController.GetCamera());
	Jass::Renderer::Submit(m_flatColorShader, m_squareVertexArray, Jass::Scale(Jass::JMat4(0.1f), Jass::JVec3(1.1f)));
	Jass::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color", Jass::GetPtr(m_squareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Jass::Event& e)
{
	m_cameraController.OnEvent(e);
}

void Sandbox2D::FlatColorSquareTest()
{
	m_flatColorShader = Jass::Shader::Create("assets/shaders/FlatColor.glsl");

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
