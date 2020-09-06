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

		FramebufferConfig fbConfig;
		fbConfig.Width = 1280;
		fbConfig.Height = 720;
		m_framebuffer = Framebuffer::Create(fbConfig);
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		JASS_PROFILE_FUNCTION();

		Renderer2D::ResetStatistics();
		m_framebuffer->Bind();

		m_cameraController.OnUpdate(ts);

		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
		RenderCommand::Clear();

		Renderer2D::BeginScene(m_cameraController.GetCamera());
		DrawQuadsTest(ts);
		//DrawSpritesTest(ts);
		Renderer2D::EndScene();
		
		m_framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		JASS_PROFILE_FUNCTION();

		static bool DockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &DockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

                ImGui::Separator();
				if (ImGui::MenuItem("Exit"))	Application::Get().Close();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

		ShowDockableGUI();

        ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_cameraController.OnEvent(e);
	}

	void EditorLayer::ShowDockableGUI()
	{
		auto statistics = Renderer2D::GetStatistics();

		ImGui::Begin("Statistics");
		ImGui::Text("Total Draw Calls: %d", statistics.DrawCalls);
		ImGui::Text("Total Quads: %d", statistics.TotalQuads);
		ImGui::Text("Total Vertices: %d", statistics.GetVertexCount());
		ImGui::Text("Total Indices: %d", statistics.GetIndexCount());
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::Begin("Viewport");
		auto viewportImgID = m_framebuffer->GetColorAttachmentRendererID();
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		JVec2 newViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		if (m_viewportSize != newViewportSize) {
			m_framebuffer->Resize((unsigned int)newViewportSize.x, (unsigned int)newViewportSize.y);
			m_cameraController.OnResize((unsigned int)newViewportSize.x, (unsigned int)newViewportSize.y);
			m_viewportSize = newViewportSize;
		}

		ImGui::Image((ImTextureID)(uint64_t)viewportImgID,
			ImVec2{ m_viewportSize.x, m_viewportSize.y },
			ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });
		ImGui::End();
		ImGui::PopStyleVar();
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