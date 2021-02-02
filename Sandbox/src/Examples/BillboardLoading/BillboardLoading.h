#ifndef BILLBOARD_LOADING_H
#define BILLBOARD_LOADING_H

#include <Jass.h>

#include "../../Sandbox3D/Terrain/Terrain.h"
#include "../../Sandbox3D/Player/PlayerController.h"

// To use billboards, you need the Billboard class which is currently on the Sandbox3D folder
#include "../../Sandbox3D/Model/Billboard.h"

class BillboardLoading : public Jass::Layer {

public:

	BillboardLoading();

	virtual ~BillboardLoading() = default;

	virtual void OnAttach() override;

	virtual void OnDetach() override;

	virtual void OnImGuiRender() override;

	virtual void OnUpdate(Jass::Timestep ts) override;

	virtual void OnEvent(Jass::Event& e) override;

private:
	PlayerController m_playerController;

	// You need a Billboard object for each billboard you want in your scene
	Billboard m_billboard;

	Jass::JVec3 m_billboardPosition;
	Jass::JVec3 m_billboardScale;
	
	int m_billboardIsCylindrical;

	bool m_isCursorDisabled;
	bool m_isFlyMode;

	Terrain m_terrain;

	Light m_light;

	Jass::ShaderLibrary m_shaderLib;

	void LoadShaders();
	void LoadTerrainTextures();
	void LoadBillboards();

	void UpdateBillboard();

	void FixCameraToTerrain();

	bool OnKeyPressedEvent(Jass::KeyPressedEvent& e);

};

#endif // !BILLBOARD_LOADING_H
