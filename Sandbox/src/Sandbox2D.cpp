#include "Sandbox2D.h"
#include <imgui.h>

Sandbox2D::Sandbox2D() :
	Layer("Sandbox2D"), m_cameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	//FlatColorSquareTest();
	m_texture = Jass::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Jass::Timestep ts)
{
	JASS_PROFILE_FUNCTION();

	m_cameraController.OnUpdate(ts);

	Jass::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
	Jass::RenderCommand::Clear();

	Jass::Renderer2D::BeginScene(m_cameraController.GetCamera());
	Jass::Renderer2D::DrawQuad({ 0.5f, 0.75f }, { 1.0f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });
	Jass::Renderer2D::DrawQuad({ 0.25f, -0.5f }, { 0.25f, 0.5f }, { 0.3f, 0.2f, 0.8f, 1.0f });
	Jass::Renderer2D::DrawRotatedQuad({ 1.0f, -0.75f }, Jass::Radians(45.0f), { 1.1f, 0.5f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Jass::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_texture, 10);
	Jass::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	JASS_PROFILE_FUNCTION();

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
