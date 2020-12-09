#ifndef SANDBOX3D_H
#define SANDBOX3D_H

#include <Jass.h>
#include "Model/Model.h"
#include "Terrain/Terrain.h"

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
	
	Light m_light;

	Model m_model;

	Terrain m_terrain;

	Jass::ShaderLibrary m_shaderLib;

};

#endif // !SANDBOX3D_H
