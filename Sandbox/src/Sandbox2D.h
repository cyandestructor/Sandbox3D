#ifndef SANDBOX2D_H
#define SANDBOX2D_H

#include <Jass.h>

class Sandbox2D : public Jass::Layer {

public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Jass::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Jass::Event& e) override;

private:
	Jass::OrthographicCameraController m_cameraController;

	Jass::Ref<Jass::Texture2D> m_texture;

	Jass::Ref<Jass::Texture2D> m_tileMap;
	Jass::Ref<Jass::SubTexture2D> m_tileCar;
	Jass::Ref<Jass::SubTexture2D> m_tileTaxi;

	void DrawQuadsTest(Jass::Timestep ts);
	void DrawSpritesTest(Jass::Timestep ts);

};

#endif // !SANDBOX2D_H
