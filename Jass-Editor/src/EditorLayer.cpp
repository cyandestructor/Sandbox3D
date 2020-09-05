#include "EditorLayer.h"
#include <imgui.h>

namespace Jass {

	EditorLayer::EditorLayer() :
		Layer("EditorLayer"), m_cameraController(1280.0f / 720.0f)
	{
	}

	void EditorLayer::OnAttach()
	{
		m_texture = Texture2D::Create("assets/textures/Checkerboard.png");

		m_tileMap = Texture2D::Create("assets/textures/Tilemap/tilemap_packed.png");
		m_tileCar = SubTexture2D::Create(m_tileMap, { 15.0f * 16.0f, 0.0f }, { 32.0f, 32.0f });
		m_tileTaxi = SubTexture2D::Create(m_tileMap, { 15.0f * 16.0f, 2.0f * 16.0f }, { 32.0f, 32.0f });
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		JASS_PROFILE_FUNCTION();

		Renderer2D::ResetStatistics();

		m_cameraController.OnUpdate(ts);

		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
		RenderCommand::Clear();

		Renderer2D::BeginScene(m_cameraController.GetCamera());
		DrawQuadsTest(ts);
		//DrawSpritesTest(ts);
		Renderer2D::EndScene();
	}

	void EditorLayer::OnImGuiRender()
	{
		JASS_PROFILE_FUNCTION();

		auto statistics = Renderer2D::GetStatistics();

		ImGui::Begin("Statistics");
		ImGui::Text("Total Draw Calls: %d", statistics.DrawCalls);
		ImGui::Text("Total Quads: %d", statistics.TotalQuads);
		ImGui::Text("Total Vertices: %d", statistics.GetVertexCount());
		ImGui::Text("Total Indices: %d", statistics.GetIndexCount());
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_cameraController.OnEvent(e);
	}

	void EditorLayer::DrawQuadsTest(Timestep ts)
	{
		static float rotation = 0.0f;
		rotation += 30.0f * ts;
		rotation = rotation > 360.0f ? rotation - 360.0f : rotation;

		Renderer2D::DrawQuad({ 0.5f, 0.75f }, { 1.0f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });
		Renderer2D::DrawQuad({ 0.25f, -0.5f }, { 0.25f, 0.5f }, { 0.3f, 0.2f, 0.8f, 1.0f });
		Renderer2D::DrawRotatedQuad({ 1.0f, -0.75f }, Radians(rotation), { 1.1f, 0.5f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_texture, 10.0f);

		JVec4 color = { 1.0f, 0.5f, 1.0f, 1.0f };
		for (float x = -5.0f; x < 5.0f; x += 0.5f) {
			for (float y = -5.0f; y < 5.0f; y += 0.5f) {
				color.r = (x + 5.0f) / 10.0f;
				color.b = (y + 5.0f) / 10.0f;
				Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
	}

	void EditorLayer::DrawSpritesTest(Timestep ts)
	{
		Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_tileCar);
		Renderer2D::DrawQuad({ 2.0f, 0.0f }, { 1.0f, 1.0f }, m_tileTaxi);
	}

}