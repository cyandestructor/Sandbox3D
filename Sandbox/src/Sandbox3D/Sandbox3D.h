#ifndef SANDBOX3D_H
#define SANDBOX3D_H

#include <Jass.h>
#include "Model/Model.h"
#include "Model/GameObject.h"
#include "Terrain/Terrain.h"
#include "Skybox/Skybox.h"
#include "Water/Water.h"
#include "Model/Billboard.h"

class Sandbox3D : public Jass::Layer {

public:
	Sandbox3D();
	virtual ~Sandbox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;
	virtual void OnUpdate(Jass::Timestep ts) override;
	virtual void OnEvent(Jass::Event& e) override;

private:
	Jass::PerspectiveCameraController m_cameraController;
	
	float m_skyRotation = 0.0f;
	float m_blendNight = 0.0f;
	float m_blendMorning = 0.0f;
	Skybox m_skybox;

	Light m_light;

	Model m_testModel;

	Model m_sunModel;
	//GameObject m_testObject;

	std::vector<Model> m_sceneModels;
	std::vector<Billboard> m_sceneBillboards;

	//Billboard m_testBillboard;

	Terrain m_terrain;

	Water m_water;
	float m_waterMotion = 0.0f;
	float m_waterMotionSpeed = 0.03f;

	Jass::ShaderLibrary m_shaderLib;

	Jass::JVec3 m_lightDirection = Jass::JVec3(0.0f);
	float m_lightAngle = 0.0f;
	float m_totalColor = 0.9f;
	float m_ambientReduction = 0.0f;
	float m_diffuseReduction = 0.0f;

	Jass::JVec3 m_modelPosition = Jass::JVec3(0.0f);
	Jass::JVec3 m_modelScale = Jass::JVec3(1.0f);

	bool m_loadAllModels = true;
	bool m_flyMode = false;
	bool m_disableCursor = true;

	bool OnKeyPressedEvent(Jass::KeyPressedEvent& e);
	bool OnJoystickConnectionEvent(Jass::JoystickConnectionEvent& e);

	void GamepadUpdate();

	void FixCameraToTerrain();
	void UpdateCollisions(Jass::Timestep ts);

	void UpdateDayCycle(Jass::Timestep ts);

	void LoadSkyboxTextures();

	void LoadModels();
	void LoadBillboards();

	void PrepareWaterReflection(Jass::Timestep ts);
	void PrepareWaterRefraction(Jass::Timestep ts);
	void RenderScene(Jass::Timestep ts);
	void RenderWaterScene(Jass::Timestep ts, const Jass::JVec4& clipPlane = Jass::JVec4(0.0f));
};

#endif // !SANDBOX3D_H
