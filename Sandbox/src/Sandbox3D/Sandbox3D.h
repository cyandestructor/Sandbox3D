#ifndef SANDBOX3D_H
#define SANDBOX3D_H

#include <Jass.h>
#include "Model/Model.h"
#include "Terrain/Terrain.h"
#include "Skybox/Skybox.h"
#include "Water/Water.h"

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
	
	Skybox m_skybox;

	Light m_light;

	Model m_model;

	Terrain m_terrain;

	Water m_water;
	float m_waterMotion = 0.0f;
	float m_waterMotionSpeed = 0.03f;

	Jass::ShaderLibrary m_shaderLib;

	void FixCameraToTerrain();

	void PrepareWaterReflection(Jass::Timestep ts);
	void PrepareWaterRefraction(Jass::Timestep ts);
	void RenderScene(Jass::Timestep ts, const Jass::JVec4& clipPlane = Jass::JVec4(0.0f));

};

#endif // !SANDBOX3D_H
