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

	Jass::Ref<Jass::VertexArray> m_squareVertexArray;
	Jass::Ref<Jass::Shader> m_flatColorShader;
	Jass::JVec4 m_squareColor = Jass::JVec4(0.2f, 0.3f, 0.8f, 1.0f);

	void FlatColorSquareTest();

};

#endif // !SANDBOX2D_H
