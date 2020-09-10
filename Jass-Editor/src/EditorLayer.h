#ifndef EDITOR_LAYER_H
#define EDITOR_LAYER_H

#include <Jass.h>

namespace Jass {

	class EditorLayer : public Layer {

	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

	private:
		OrthographicCameraController m_cameraController;

		Ref<Texture2D> m_texture;

		Ref<Scene> m_scene;

		Ref<Framebuffer> m_framebuffer;

		bool m_isViewportFocused = false;
		JVec2 m_viewportSize = JVec2(0.0f);

		void ShowDockableGUI();

		void DrawViewport();

	};

}

#endif // !EDITOR_LAYER_H
