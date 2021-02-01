#ifndef TERRAIN_LOADING_H
#define TERRAIN_LOADING_H

#include <Jass.h>

// You need to include the Terrain class which is currently on the Sandbox3D folder
#include "../../Sandbox3D/Terrain/Terrain.h"
// Include this file to use a Built-in player controller that supports keyboard and mouse or gamepad input
#include "../../Sandbox3D/Player/PlayerController.h"

class TerrainLoading : public Jass::Layer {

public:

	TerrainLoading();

	virtual ~TerrainLoading() = default;

	virtual void OnAttach() override;

	virtual void OnDetach() override;

	virtual void OnImGuiRender() override;

	virtual void OnUpdate(Jass::Timestep ts) override;

	virtual void OnEvent(Jass::Event& e) override;

private:
	// This is a Built-in player controller. It has a camera that represents the player eyes
	PlayerController m_playerController;

	bool m_isCursorDisabled;
	bool m_isFlyMode;

	// Declare a terrain as a member of your scene. Most times you will only need one
	Terrain m_terrain;

	float m_terrainUVRepeat;
	float m_ambientReduction;
	float m_diffuseReduction;
	
	Jass::JVec3 m_terrainPosition;

	Light m_light;

	Jass::ShaderLibrary m_shaderLib;

	void LoadShaders();
	void LoadTerrainTextures();

	void UpdateTerrain();

	void FixCameraToTerrain();

	bool OnKeyPressedEvent(Jass::KeyPressedEvent& e);

};

#endif // !TERRAIN_LOADING_H
