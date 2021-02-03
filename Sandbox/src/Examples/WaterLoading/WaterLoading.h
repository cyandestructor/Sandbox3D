#ifndef WATER_LOADING_H
#define WATER_LOADING_H

#include <Jass.h>

#include "../../Sandbox3D/Terrain/Terrain.h"
#include "../../Sandbox3D/Player/PlayerController.h"
#include "../../Sandbox3D/Skybox/Skybox.h"
#include "../../Sandbox3D/Model/Model.h"

// To create a water plane, you will need to include the water class which is in the Sandbox3D folder
#include "../../Sandbox3D/Water/Water.h"

class WaterLoading : public Jass::Layer {

public:

	WaterLoading();

	virtual ~WaterLoading() = default;

	virtual void OnAttach() override;

	virtual void OnDetach() override;

	virtual void OnImGuiRender() override;

	virtual void OnUpdate(Jass::Timestep ts) override;

	virtual void OnEvent(Jass::Event& e) override;

private:
	PlayerController m_playerController;

	bool m_isCursorDisabled;
	bool m_isFlyMode;

	Model m_model;

	Terrain m_terrain;

	float m_ambientReduction;

	Skybox m_skybox;

	float m_skyboxRotation;

	Light m_light;

	// You will need one Water object for each water plane you want in your scene
	Water m_water;

	float m_waterMotion;
	float m_waterMotionSpeed;

	float m_waterReflectivity;
	float m_waterShineDamper;
	float m_tilingFactor;
	float m_waterDistortion;

	Jass::JVec3 m_waterPosition;
	Jass::JVec4 m_waterColor;

	Jass::ShaderLibrary m_shaderLib;

	void LoadShaders();
	void LoadModels();
	void LoadTerrainTextures();
	void LoadSkyboxTextures();
	void LoadWater();

	void RenderScene(Jass::Timestep ts);

	void UpdateTerrain();
	void UpdateSkybox(Jass::Timestep ts);
	void UpdateModel();

	void ClampValues();
	void UpdateWater(Jass::Timestep ts);
	void PrepareWaterReflection(Jass::Timestep ts);
	void PrepareWaterRefraction(Jass::Timestep ts);
	void RenderWaterScene(Jass::Timestep ts, const Jass::JVec4& clipPlane = Jass::JVec4(0.0f));

	void FixCameraToTerrain();

	bool OnKeyPressedEvent(Jass::KeyPressedEvent& e);
	bool OnWindowResizeEvent(Jass::WindowResizeEvent& e);

};

#endif // !WATER_LOADING_H
