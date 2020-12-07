#ifndef SANDBOX3D_H
#define SANDBOX3D_H

#include <Jass.h>
#include "Model/Model.h"

class Sandbox3D : public Jass::Layer {

public:
	Sandbox3D();
	virtual ~Sandbox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Jass::Timestep ts) override;
	virtual void OnEvent(Jass::Event& e) override;

private:
	Jass::PerspectiveCameraController m_cameraController;
	Model m_cube;

};

#endif // !SANDBOX3D_H
