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

		Ref<Texture2D> m_tileMap;
		Ref<SubTexture2D> m_tileCar;
		Ref<SubTexture2D> m_tileTaxi;

		void DrawQuadsTest(Timestep ts);
		void DrawSpritesTest(Timestep ts);
	};

}

#endif // !EDITOR_LAYER_H
