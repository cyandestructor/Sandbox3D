#include "Sandbox3D.h"
#include <imgui.h>

Sandbox3D::Sandbox3D()
	: m_light({ 10.0f, 500.0f, 100.0f }, { 1.0f,1.0f,1.0f,1.0f }),
	m_terrain("assets/textures/Sandbox3D/heightmap.png", 300, 300, 2.0f),
	m_water({ 600.0f, 600.0f })
{
	m_cameraController.GetCamera().SetProjection(60.0f, 1280.0f, 720.0f, 0.01f, 1000.0f);
	
	m_shaderLib.Load("BasicMaterial", "assets/shaders/BasicMaterial.glsl");
	m_shaderLib.Load("NormalsMaterial", "assets/shaders/NormalsMaterial.glsl");
	m_shaderLib.Load("TerrainMaterial", "assets/shaders/TerrainShader.glsl");
	m_shaderLib.Load("SkyboxShader", "assets/shaders/SkyboxShader.glsl");
	m_shaderLib.Load("WaterMaterial", "assets/shaders/WaterShader.glsl");
	m_shaderLib.Load("SphericalBillboard", "assets/shaders/SphericalBillboardShader.glsl");
	m_shaderLib.Load("CylindricalBillboard", "assets/shaders/CylindricalBillboardShader.glsl");
}

void Sandbox3D::OnAttach()
{
	LoadSkyboxTextures();
	LoadModels();
	LoadBillboards();

	Jass::Input::SetCursorMode(Jass::CursorMode::Disabled);

	m_terrain.SetBlendMap("assets/textures/Terrain/blendTest.jpg");
	m_terrain.AddTexture("assets/textures/Terrain/grass.jpg", "u_diffuseTex", 1);
	m_terrain.AddTexture("assets/textures/Terrain/grassNorm.jpg", "u_normalTex", 2);
	m_terrain.AddTexture("assets/textures/Terrain/sand.png", "u_diffuseTexR", 3);
	m_terrain.AddTexture("assets/textures/Terrain/sandNorm.png", "u_normalTexR", 4);
	m_terrain.AddTexture("assets/textures/Terrain/dirt.jpg", "u_diffuseTexG", 5);
	m_terrain.AddTexture("assets/textures/Terrain/dirtNorm.jpg", "u_normalTexG", 6);
	m_terrain.AddTexture("assets/textures/Terrain/snow.jpg", "u_diffuseTexB", 7);
	m_terrain.AddTexture("assets/textures/Terrain/snowNorm.jpg", "u_normalTexB", 8);
	m_terrain.SetUVRepeat(10.0f);
	m_terrain.SetPosition({ -300.0f, 0.0f, 300.0f });

	//m_testObject.LoadModel("assets/models/sphere.obj");
	//m_testObject.SetCollisionBox(100.0f, 100.0f, 100.0f);
	//m_testObject.GetModel()->GetMaterial().SetDiffuseTexture("assets/textures/Sandbox3D/Dirt/dirt_color.jpg");
	//m_testObject.GetModel()->GetMaterial().SetNormalTexture("assets/textures/Sandbox3D/Dirt/dirt_norm.jpg");
	//m_testObject.GetModel()->SetPosition({ 50.0f, 70.0f, 0.0f });

	m_sunModel.Load("assets/models/sphere.obj");
	m_sunModel.GetMaterial().SetDiffuseTexture("assets/textures/Sandbox3D/Dirt/dirt_color.jpg");
	m_sunModel.GetMaterial().SetNormalTexture("assets/textures/Sandbox3D/Dirt/dirt_norm.jpg");

	m_water.SetPosition({ 0.0f, 25.0f, 0.0f });
	m_water.SetColor({ 0.2f, 0.6f, 0.8f, 1.0f });
	m_water.SetTilingFactor(7.0f);
	m_water.SetDistortionFactor(0.02f);
	m_water.SetSpecularProperties(0.5f, 1.0f);
	m_water.SetTextures("assets/textures/Water/dudv.png", "assets/textures/Water/normal.png");
}

void Sandbox3D::OnDetach()
{
}

void Sandbox3D::OnImGuiRender()
{
	// This is the GUI Layer: Search for ImGui to know more

	//ImGui::Begin("Settings");
	//ImGui::InputFloat3("Model position", Jass::GetPtr(m_modelPosition), 3);
	//ImGui::InputFloat3("Model scale", Jass::GetPtr(m_modelScale), 3);
	//ImGui::End();
}

void Sandbox3D::OnUpdate(Jass::Timestep ts)
{
	UpdateDayCycle(ts);

	if (!m_flyMode)
		FixCameraToTerrain();

	//UpdateCollisions(ts);
	
	m_cameraController.OnUpdate(ts);

	Jass::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
	Jass::RenderCommand::Clear();

	PrepareWaterReflection(ts);
	PrepareWaterRefraction(ts);

	Jass::Renderer::BeginScene(m_cameraController.GetCamera());
	RenderScene(ts);
	Jass::Renderer::EndScene();
}

void Sandbox3D::OnEvent(Jass::Event& e)
{
	m_cameraController.OnEvent(e);
	Jass::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Jass::KeyPressedEvent>(BIND_EVENT_FN(Sandbox3D::OnKeyPressedEvent));
}

bool Sandbox3D::OnKeyPressedEvent(Jass::KeyPressedEvent& e)
{
	switch (e.GetKeyCode())
	{
		case JASS_KEY_ESCAPE:
			Jass::Application::Get().Close();
			break;
		case JASS_KEY_F:
			m_flyMode = !m_flyMode;
			break;
		case JASS_KEY_P:
			if (m_disableCursor) {
				Jass::Input::SetCursorMode(Jass::CursorMode::Normal);
				m_disableCursor = false;
			}
			else {
				Jass::Input::SetCursorMode(Jass::CursorMode::Disabled);
				m_disableCursor = true;
			}
			break;
		default:
			break;
	}

	return false;
}

void Sandbox3D::FixCameraToTerrain()
{
	auto cameraPosition = m_cameraController.GetCamera().GetPosition();
	cameraPosition.y = m_terrain.GetTerrainHeight(cameraPosition.x, cameraPosition.z);
	cameraPosition.y += 20.0f;
	m_cameraController.GetCamera().SetPosition(cameraPosition);
}

void Sandbox3D::UpdateCollisions(Jass::Timestep ts)
{
	//m_testObject.OnUpdate(ts);
	//if (m_testObject.HasCollisionBox()) {
	//	//m_cameraController.OnUpdate(ts);
	//	const auto& cameraPosition = m_cameraController.GetCamera().GetPosition();
	//	if (m_testObject.GetCollisionBox()->Collision(cameraPosition)) {
	//		m_cameraController.SetCollision(true);
	//		//m_cameraController.GetCamera().SetPosition(cameraPosition);
	//		//m_cameraController.CalculateCamera();
	//		JASS_LOG_INFO("Collision");
	//		//m_cameraController.OnUpdate(ts);
	//	}
	//	else {
	//		m_cameraController.SetCollision(false);
	//	}
	//}
}

void Sandbox3D::UpdateDayCycle(Jass::Timestep ts)
{
	unsigned int day = 0, morning = 1, night = 2;
	
	m_skyRotation += 1.0f * ts;
	m_skyRotation = m_skyRotation >= 360 ? 0.0f : m_skyRotation;

	m_skybox.SetRotation(m_skyRotation);

	m_lightAngle += 5.0f * ts;
	m_lightAngle = m_lightAngle >= 360 ? 0.0f : m_lightAngle;

	if (m_lightAngle > 160.0f) {
		// Set the light color to a darker one (night)
		m_totalColor -= 0.1f * ts;
		m_totalColor = std::max(m_totalColor, 0.3f);

		if (m_lightAngle < 340) {
			// Transition of the skybox from day to night
			m_blendNight += 0.1f * ts;
			m_blendNight = std::min(m_blendNight, 1.0f);
			m_skybox.BlendTextures(day, night, m_blendNight);
		}
	}
	else {
		// Set the light color to a lighter one (morning/day)
		m_totalColor += 0.1f * ts;
		m_totalColor = std::min(m_totalColor, 0.9f);

		if (m_lightAngle <= 80.0f) {
			// Transition of the skybox from morning to day
			m_blendMorning -= 0.1f * ts;
			m_blendMorning = std::max(m_blendMorning, 0.0f);
			m_skybox.BlendTextures(day, morning, m_blendMorning);
		}
	}

	if (m_lightAngle >= 320.0f) {
		// Transition of the skybox from night to morning
		m_blendNight -= 0.2f * ts;
		m_blendMorning += 0.2f * ts;
		m_blendNight = std::max(m_blendNight, 0.0f);
		m_blendMorning = std::min(m_blendMorning, 1.0f);
		m_skybox.BlendTextures(morning, night, m_blendNight);
	}

	m_light.SetColor({ m_totalColor, m_totalColor, m_totalColor, 1.0f });

	// Position the light (sun) in a circle path around the scene
	// Uncomment the m_sunModel.Render call in the RenderScene method to look the physical position of the sun
	m_lightDirection.x = cos(Jass::Radians(m_lightAngle)) * 500.0f;
	m_lightDirection.y = sin(Jass::Radians(m_lightAngle)) * 500.0f;
	m_lightDirection.z = 0.0f;

	m_light.SetPosition(m_lightDirection);
	m_sunModel.SetPosition(m_lightDirection);

	float lightIntensity = std::max(sin(Jass::Radians(m_lightAngle)), 0.1f);
	m_ambientReduction = m_diffuseReduction = lightIntensity;

	//m_testBillboard.GetMaterial().SetAmbientReduction(m_ambientReduction);

	for (auto& billboard : m_sceneBillboards) {
		billboard.GetMaterial().SetAmbientReduction(m_ambientReduction);
	}

	m_terrain.SetAmbientReduction(m_ambientReduction);
	m_terrain.SetDiffuseReduction(m_diffuseReduction);

	for (auto& model : m_sceneModels) {
		model.GetMaterial().SetAmbientReduction(m_ambientReduction);
		model.GetMaterial().SetDiffuseReduction(m_ambientReduction);
	}
}

void Sandbox3D::LoadSkyboxTextures()
{
	std::vector<std::string> textures
	{
		"assets/textures/Sandbox3D/Skybox/Day/right.png",
		"assets/textures/Sandbox3D/Skybox/Day/left.png",
		"assets/textures/Sandbox3D/Skybox/Day/top.png",
		"assets/textures/Sandbox3D/Skybox/Day/bottom.png",
		"assets/textures/Sandbox3D/Skybox/Day/front.png",
		"assets/textures/Sandbox3D/Skybox/Day/back.png"
	};

	std::vector<std::string> texturesMorning
	{
		"assets/textures/Sandbox3D/Skybox/Morning/right.png",
		"assets/textures/Sandbox3D/Skybox/Morning/left.png",
		"assets/textures/Sandbox3D/Skybox/Morning/top.png",
		"assets/textures/Sandbox3D/Skybox/Morning/bottom.png",
		"assets/textures/Sandbox3D/Skybox/Morning/front.png",
		"assets/textures/Sandbox3D/Skybox/Morning/back.png"
	};

	std::vector<std::string> texturesNight
	{
		"assets/textures/Sandbox3D/Skybox/Night/right.png",
		"assets/textures/Sandbox3D/Skybox/Night/left.png",
		"assets/textures/Sandbox3D/Skybox/Night/top.png",
		"assets/textures/Sandbox3D/Skybox/Night/bottom.png",
		"assets/textures/Sandbox3D/Skybox/Night/front.png",
		"assets/textures/Sandbox3D/Skybox/Night/back.png"
	};

	m_skybox.SetTexture(textures);
	m_skybox.AddTexture(texturesMorning, "u_morning", 1);
	m_skybox.AddTexture(texturesNight, "u_night", 2);
}

void Sandbox3D::LoadModels()
{
	/*m_testModel.Load("assets/models/Boat/boat.obj");
	m_testModel.GetMaterial().SetDiffuseTexture("assets/models/Boat/diffuse.png");
	m_testModel.GetMaterial().SetNormalTexture("assets/models/Boat/normal.png");
	m_testModel.Rotate({ 0.0f, 1.0f, 0.0f }, 180.0f);
	m_testModel.SetScale({ 0.1f, 0.1f, 0.1f });*/
	
	if (!m_loadAllModels)
		return;

	/*Model wall;
	wall.Load("assets/models/Wall/wall.obj");
	wall.GetMaterial().SetDiffuseTexture("assets/models/Wall/diffuse.png");
	wall.GetMaterial().SetNormalTexture("assets/models/Wall/normal2.png");
	wall.SetPosition({ -200.0f, 30.0f, -300.0f });
	wall.SetScale({ 2.0f, 2.0f, 2.0f });
	m_sceneModels.push_back(wall);

	Model wall2;
	wall2.Load("assets/models/Wall/wall.obj");
	wall2.GetMaterial().SetDiffuseTexture("assets/models/Wall/diffuse.png");
	wall2.GetMaterial().SetNormalTexture("assets/models/Wall/normal2.png");
	wall2.SetPosition({ 0.0f, 30.0f, -300.0f });
	wall2.SetScale({ 2.0f, 2.0f, 2.0f });
	m_sceneModels.push_back(wall2);

	Model wall3;
	wall3.Load("assets/models/Wall/wall.obj");
	wall3.GetMaterial().SetDiffuseTexture("assets/models/Wall/diffuse.png");
	wall3.GetMaterial().SetNormalTexture("assets/models/Wall/normal2.png");
	wall3.SetPosition({ 200.0f, 30.0f, -300.0f });
	wall3.SetScale({ 2.0f, 2.0f, 2.0f });
	m_sceneModels.push_back(wall3);*/

	/*Model wall4;
	wall4.Load("assets/models/Wall/wall.obj");
	wall4.GetMaterial().SetDiffuseTexture("assets/models/Wall/diffuse.png");
	wall4.GetMaterial().SetNormalTexture("assets/models/Wall/normal2.png");
	wall4.SetPosition({ -200.0f, 20.0f, 280.0f });
	wall4.SetScale({ 2.0f, 2.0f, 2.0f });
	m_sceneModels.push_back(wall4);

	Model wall5;
	wall5.Load("assets/models/Wall/wall.obj");
	wall5.GetMaterial().SetDiffuseTexture("assets/models/Wall/diffuse.png");
	wall5.GetMaterial().SetNormalTexture("assets/models/Wall/normal2.png");
	wall5.SetPosition({ 0.0f, 20.0f, 280.0f });
	wall5.SetScale({ 2.0f, 2.0f, 2.0f });
	m_sceneModels.push_back(wall5);

	Model wall6;
	wall6.Load("assets/models/Wall/wall.obj");
	wall6.GetMaterial().SetDiffuseTexture("assets/models/Wall/diffuse.png");
	wall6.GetMaterial().SetNormalTexture("assets/models/Wall/normal2.png");
	wall6.SetPosition({ 200.0f, 20.0f, 280.0f });
	wall6.SetScale({ 2.0f, 2.0f, 2.0f });
	m_sceneModels.push_back(wall6);*/

	//m_testModel.Load("assets/models/Stone1/stone1.obj");
	//m_testModel.GetMaterial().SetDiffuseTexture("assets/models/Stone1/diffuse.jpg");
	//m_testModel.GetMaterial().SetNormalTexture("assets/models/Stone1/normal.jpg");
	//m_testModel.Load("assets/models/Stone2/stone2.obj");
	//m_testModel.GetMaterial().SetDiffuseTexture("assets/models/Stone2/diffuse.jpg");
	//m_testModel.GetMaterial().SetNormalTexture("assets/models/Stone2/normal.jpg");
	
	///////////////////////////////////////////////

	Model stone5;
	stone5.Load("assets/models/Stone3/stone3.obj");
	stone5.GetMaterial().SetDiffuseTexture("assets/models/Stone3/diffuse.jpg");
	stone5.GetMaterial().SetNormalTexture("assets/models/Stone3/normal.jpg");
	stone5.SetPosition({ -200.0f, 23.0f, 93.0f });
	stone5.SetScale({ 0.2f,0.2f,0.2f });
	m_sceneModels.push_back(stone5);

	Model stone4;
	stone4.Load("assets/models/Stone3/stone3.obj");
	stone4.GetMaterial().SetDiffuseTexture("assets/models/Stone3/diffuse.jpg");
	stone4.GetMaterial().SetNormalTexture("assets/models/Stone3/normal.jpg");
	stone4.SetPosition({ 13.0f, 25.0f, 108.0f });
	stone4.SetScale({ 0.2f,0.2f,0.2f });
	m_sceneModels.push_back(stone4);

	Model stone;
	stone.Load("assets/models/Stone2/stone2.obj");
	stone.GetMaterial().SetDiffuseTexture("assets/models/Stone2/diffuse.jpg");
	stone.GetMaterial().SetNormalTexture("assets/models/Stone2/normal.jpg");
	stone.SetPosition({ 45.0f, 25.0f, -110.0f });
	stone.SetScale({ 0.2f,0.2f,0.2f });
	m_sceneModels.push_back(stone);

	Model stone2;
	stone2.Load("assets/models/Stone2/stone2.obj");
	stone2.GetMaterial().SetDiffuseTexture("assets/models/Stone2/diffuse.jpg");
	stone2.GetMaterial().SetNormalTexture("assets/models/Stone2/normal.jpg");
	stone2.SetPosition({ 60.0f, 25.0f, 65.0f });
	stone2.SetScale({ 0.2f,0.2f,0.2f });
	m_sceneModels.push_back(stone2);

	Model stone3;
	stone3.Load("assets/models/Stone2/stone2.obj");
	stone3.GetMaterial().SetDiffuseTexture("assets/models/Stone2/diffuse.jpg");
	stone3.GetMaterial().SetNormalTexture("assets/models/Stone2/normal.jpg");
	stone3.SetPosition({ 0.0f, 25.0f, 120.0f });
	stone3.SetScale({ 0.2f,0.2f,0.2f });
	m_sceneModels.push_back(stone3);

	Model lantern;
	lantern.Load("assets/models/Lantern/lantern.obj");
	lantern.GetMaterial().SetDiffuseTexture("assets/models/Lantern/diffuse.jpg");
	lantern.GetMaterial().SetNormalTexture("assets/models/Lantern/normal.png");
	lantern.SetPosition({ 230.0f, 45.0f, -160.0f });
	lantern.SetScale({ 12.0f, 12.0f, 12.0f });
	m_sceneModels.push_back(lantern);

	Model lantern2;
	lantern2.Load("assets/models/Lantern/lantern.obj");
	lantern2.GetMaterial().SetDiffuseTexture("assets/models/Lantern/diffuse.jpg");
	lantern2.GetMaterial().SetNormalTexture("assets/models/Lantern/normal.png");
	lantern2.SetPosition({ -150.0f, 41.0f, 220.0f });
	lantern2.SetScale({ 12.0f, 12.0f, 12.0f });
	m_sceneModels.push_back(lantern2);

	Model cabin;
	cabin.Load("assets/models/Cabin/cabin.obj");
	cabin.GetMaterial().SetDiffuseTexture("assets/models/Cabin/diffuse.jpg");
	cabin.GetMaterial().SetNormalTexture("assets/models/Cabin/normal.jpg");
	cabin.SetPosition({ -100.0f, 34.5f,-70.0f });
	m_sceneModels.push_back(cabin);
	
	Model cabin2;
	cabin2.Load("assets/models/Cabin2/cabin2.obj");
	cabin2.GetMaterial().SetDiffuseTexture("assets/models/Cabin2/diffuse.png");
	cabin2.GetMaterial().SetNormalTexture("assets/models/Cabin2/normal.png");
	cabin2.SetPosition({ -70.0f, 31.0f, 250.0f });
	cabin2.Rotate({ 0.0f, 1.0f, 0.0f }, 180.0f);
	cabin2.SetScale({ 0.12f,0.12f,0.12f });
	m_sceneModels.push_back(cabin2);

	Model cabin3;
	cabin3.Load("assets/models/Cabin3/cabin3.obj");
	cabin3.GetMaterial().SetDiffuseTexture("assets/models/Cabin3/diffuse.png");
	cabin3.GetMaterial().SetNormalTexture("assets/models/Cabin3/normal.png");
	cabin3.SetPosition({ 170.0f, 34.0f, -170.0f });
	cabin3.Rotate({ 0.0f, 1.0f, 0.0f }, 180.0f);
	cabin3.SetScale({ 0.07f,0.07f,0.07f });
	m_sceneModels.push_back(cabin3);
}

void Sandbox3D::LoadBillboards()
{
	Billboard arbol;
	arbol.SetPosition({ 0.0f, 52.0f, 200.0f });
	arbol.SetScale({ 30.0f, 50.0f, 1.0f });
	arbol.GetMaterial().SetDiffuseTexture("assets/textures/Billboard/arbol.png");
	arbol.SetType(BillboardType::Cylindrical);
	m_sceneBillboards.push_back(arbol);

	Billboard cesped;
	cesped.SetPosition({ 100.0f, 44.0f, 150.0f });
	cesped.SetScale({ 15.0f, 15.0f, 1.0f });
	cesped.GetMaterial().SetDiffuseTexture("assets/textures/Billboard/billboard.png");
	m_sceneBillboards.push_back(cesped);
}

void Sandbox3D::PrepareWaterReflection(Jass::Timestep ts)
{
	auto cameraPosition = m_cameraController.GetCamera().GetPosition();
	float pitch = m_cameraController.GetPitch();

	// Move the camera below the water and inverse its pitch to get the reflection
	Jass::JVec3 reflectionCameraPosition = cameraPosition;
	float distance = 2.0f * (cameraPosition.y - m_water.GetPosition().y);
	float inversePitch = -pitch;
	reflectionCameraPosition.y -= distance;
	m_cameraController.GetCamera().SetPosition(reflectionCameraPosition);
	m_cameraController.SetPitch(inversePitch);
	m_cameraController.OnUpdate(ts);

	Jass::Renderer::BeginScene(m_cameraController.GetCamera());

	m_water.BeginReflection();
	Jass::RenderCommand::EnableClipDistance(true);
	RenderWaterScene(ts, { 0.0f, 1.0f, 0.0f, -m_water.GetPosition().y });
	Jass::RenderCommand::EnableClipDistance(false);
	m_skybox.Render(m_shaderLib.GetShader("SkyboxShader"), m_cameraController.GetCamera());
	m_water.EndReflection();
	
	Jass::Renderer::EndScene();

	m_cameraController.GetCamera().SetPosition(cameraPosition);
	m_cameraController.SetPitch(pitch);
	m_cameraController.OnUpdate(ts);
}

void Sandbox3D::PrepareWaterRefraction(Jass::Timestep ts)
{
	Jass::Renderer::BeginScene(m_cameraController.GetCamera());

	m_water.BeginRefraction();
	Jass::RenderCommand::EnableClipDistance(true);
	RenderWaterScene(ts, { 0.0f, -1.0f, 0.0f, m_water.GetPosition().y + 1.0f });
	Jass::RenderCommand::EnableClipDistance(false);
	m_skybox.Render(m_shaderLib.GetShader("SkyboxShader"), m_cameraController.GetCamera());
	m_water.EndRefraction();

	Jass::Renderer::EndScene();
}

void Sandbox3D::RenderScene(Jass::Timestep ts)
{
	m_shaderLib.GetShader("NormalsMaterial")->Bind();
	m_shaderLib.GetShader("NormalsMaterial")->SetFloat3("u_cameraPosition", m_cameraController.GetCamera().GetPosition());
	
	//m_sunModel.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light);

	for (const auto& model : m_sceneModels) {
		model.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light);
	}

	//m_testModel.SetPosition(m_modelPosition);
	//m_testModel.SetScale(m_modelScale);
	//m_testModel.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light);
	
	//m_testObject.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light);

	//m_testBillboard.Render(m_shaderLib.GetShader("CylindricalBillboard"), m_light, m_cameraController.GetCamera());

	for (auto& billboard : m_sceneBillboards) {
		if (billboard.GetType() == BillboardType::Cylindrical)
			billboard.Render(m_shaderLib.GetShader("CylindricalBillboard"), m_light, m_cameraController.GetCamera());
		else
			billboard.Render(m_shaderLib.GetShader("SphericalBillboard"), m_light, m_cameraController.GetCamera());
	}

	m_terrain.Render(m_shaderLib.GetShader("TerrainMaterial"), m_light);

	m_waterMotion += m_waterMotionSpeed * ts;
	m_waterMotion = m_waterMotion > 1.0f ? 0.0f : m_waterMotion;
	m_water.SetMotionFactor(m_waterMotion);
	m_water.Render(m_shaderLib.GetShader("WaterMaterial"), m_light, m_cameraController.GetCamera());

	m_skybox.Render(m_shaderLib.GetShader("SkyboxShader"), m_cameraController.GetCamera());
}

void Sandbox3D::RenderWaterScene(Jass::Timestep ts, const Jass::JVec4& clipPlane)
{
	m_shaderLib.GetShader("NormalsMaterial")->Bind();
	m_shaderLib.GetShader("NormalsMaterial")->SetFloat3("u_cameraPosition", m_cameraController.GetCamera().GetPosition());
	
	//m_sunModel.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light, clipPlane);
	
	for (const auto& model : m_sceneModels) {
		model.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light, clipPlane);
	}
	
	for (auto& billboard : m_sceneBillboards) {
		if (billboard.GetType() == BillboardType::Cylindrical)
			billboard.Render(m_shaderLib.GetShader("CylindricalBillboard"), m_light, m_cameraController.GetCamera());
		else
			billboard.Render(m_shaderLib.GetShader("SphericalBillboard"), m_light, m_cameraController.GetCamera());
	}

	//m_testObject.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light, clipPlane);

	//m_testBillboard.Render(m_shaderLib.GetShader("SphericalBillboard"), m_light, m_cameraController.GetCamera());

	m_terrain.Render(m_shaderLib.GetShader("TerrainMaterial"), m_light, clipPlane);
}
