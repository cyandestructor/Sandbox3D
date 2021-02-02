#ifndef SKYBOX_LOADING_H
#define SKYBOX_LOADING_H

#include <Jass.h>

#include "../../Sandbox3D/Terrain/Terrain.h"
#include "../../Sandbox3D/Player/PlayerController.h"

// To create a Skybox you need the Skybox class which is currently on the Sandbox3D folder
#include "../../Sandbox3D/Skybox/Skybox.h"

class SkyboxLoading : public Jass::Layer {

public:

	SkyboxLoading();

	virtual ~SkyboxLoading() = default;

	virtual void OnAttach() override;

	virtual void OnDetach() override;

	virtual void OnImGuiRender() override;

	virtual void OnUpdate(Jass::Timestep ts) override;

	virtual void OnEvent(Jass::Event& e) override;

private:
	PlayerController m_playerController;

	bool m_isCursorDisabled;
	bool m_isFlyMode;

	Terrain m_terrain;

	// You will need a Skybox as a member of your scene, usually one is enough
	Skybox m_skybox;

	float m_skyboxTextureBlend;
	float m_skyboxRotation;

	Light m_light;

	Jass::ShaderLibrary m_shaderLib;

	void LoadShaders();
	void LoadTerrainTextures();
	void LoadSkyboxTextures();

	void UpdateSkybox(Jass::Timestep ts);

	void FixCameraToTerrain();

	bool OnKeyPressedEvent(Jass::KeyPressedEvent& e);

};

#endif // !SKYBOX_LOADING_H
