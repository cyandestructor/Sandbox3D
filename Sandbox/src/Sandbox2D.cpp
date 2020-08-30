#include "Sandbox2D.h"
#include <imgui.h>

Sandbox2D::Sandbox2D() :
	Layer("Sandbox2D"), m_cameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
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

	static float rotation = 0.0f;
	rotation += 30.0f * ts;
	rotation = rotation > 360.0f ? rotation - 360.0f : rotation;

	Jass::Renderer2D::BeginScene(m_cameraController.GetCamera());
	Jass::Renderer2D::DrawQuad({ 0.5f, 0.75f }, { 1.0f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });
	Jass::Renderer2D::DrawQuad({ 0.25f, -0.5f }, { 0.25f, 0.5f }, { 0.3f, 0.2f, 0.8f, 1.0f });
	Jass::Renderer2D::DrawRotatedQuad({ 1.0f, -0.75f }, Jass::Radians(rotation), { 1.1f, 0.5f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Jass::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_texture, 10.0f);
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
