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
}

void Sandbox3D::OnAttach()
{
	LoadSkyboxTextures();
	//LoadModels();

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

	m_testObject.LoadModel("assets/models/sphere.obj");
	m_testObject.SetCollisionBox(100.0f, 100.0f, 100.0f);
	m_testObject.GetModel()->GetMaterial().SetDiffuseTexture("assets/textures/Sandbox3D/Dirt/dirt_color.jpg");
	m_testObject.GetModel()->GetMaterial().SetNormalTexture("assets/textures/Sandbox3D/Dirt/dirt_norm.jpg");
	m_testObject.GetModel()->SetPosition({ 50.0f, 70.0f, 0.0f });

	m_model.Load("assets/models/sphere.obj");
	m_model.GetMaterial().SetDiffuseTexture("assets/textures/Sandbox3D/Dirt/dirt_color.jpg");
	m_model.GetMaterial().SetNormalTexture("assets/textures/Sandbox3D/Dirt/dirt_norm.jpg");
	m_model.SetPosition({ 0.0f, 70.0f, 0.0f });
	m_model.GetMaterial().SetSpecularSettings(0.0f, 0.0f);

	m_water.SetPosition({ 0.0f, 25.0f, 0.0f });
	m_water.SetColor({ 0.2f, 0.6f, 0.8f, 1.0f });
	m_water.SetTilingFactor(7.0f);
	m_water.SetDistortionFactor(0.02f);
	m_water.SetSpecularProperties(0.5f, 1.0f);
	m_water.SetTextures("assets/textures/Water/dudv.png", "assets/textures/Water/normal.png");

	m_testBillboard.SetPosition({ -10.0f, 50.0f, 0.0f });
	m_testBillboard.SetScale({ 30.0f, 30.0f, 30.0f });
	m_testBillboard.GetMaterial().SetDiffuseTexture("assets/textures/Billboard/billboard.png");
}

void Sandbox3D::OnDetach()
{
}

void Sandbox3D::OnImGuiRender()
{
	//ImGui::Begin("Settings");
	//ImGui::InputFloat3("Model position", Jass::GetPtr(m_modelPosition), 3);
	//ImGui::InputFloat3("Model scale", Jass::GetPtr(m_modelScale), 3);
	//ImGui::End();
}

void Sandbox3D::OnUpdate(Jass::Timestep ts)
{
	// Close the application
	if (Jass::Input::IsKeyPressed(JASS_KEY_ESCAPE))
		Jass::Application::Get().Close();

	if (Jass::Input::IsKeyPressed(JASS_KEY_F))
		m_flyMode = !m_flyMode;

	//UpdateDayCycle(ts);

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
	m_testObject.OnUpdate(ts);
	if (m_testObject.HasCollisionBox()) {
		//m_cameraController.OnUpdate(ts);
		const auto& cameraPosition = m_cameraController.GetCamera().GetPosition();
		if (m_testObject.GetCollisionBox()->Collision(cameraPosition)) {
			m_cameraController.SetCollision(true);
			//m_cameraController.GetCamera().SetPosition(cameraPosition);
			//m_cameraController.CalculateCamera();
			JASS_LOG_INFO("Collision");
			//m_cameraController.OnUpdate(ts);
		}
		else {
			m_cameraController.SetCollision(false);
		}
	}
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
		m_totalColor -= 0.1f * ts;
		m_totalColor = std::max(m_totalColor, 0.3f);

		if (m_lightAngle < 340) {
			m_blendNight += 0.1f * ts;
			m_blendNight = std::min(m_blendNight, 1.0f);
			m_skybox.BlendTextures(day, night, m_blendNight);
		}
	}
	else {
		m_totalColor += 0.1f * ts;
		m_totalColor = std::min(m_totalColor, 0.9f);

		if (m_lightAngle <= 80.0f) {
			m_blendMorning -= 0.1f * ts;
			m_blendMorning = std::max(m_blendMorning, 0.0f);
			m_skybox.BlendTextures(day, morning, m_blendMorning);
		}
	}

	if (m_lightAngle >= 320.0f) {

		m_blendNight -= 0.2f * ts;
		m_blendMorning += 0.2f * ts;
		m_blendNight = std::max(m_blendNight, 0.0f);
		m_blendMorning = std::min(m_blendMorning, 1.0f);
		m_skybox.BlendTextures(morning, night, m_blendNight);
	}

	m_light.SetColor({ m_totalColor, m_totalColor, m_totalColor, 1.0f });

	m_lightDirection.x = cos(Jass::Radians(m_lightAngle)) * 200.0f;
	m_lightDirection.y = sin(Jass::Radians(m_lightAngle)) * 200.0f;
	m_lightDirection.z = 0.0f;

	m_light.SetPosition(m_lightDirection);

	float lightIntensity = std::max(sin(Jass::Radians(m_lightAngle)), 0.1f);
	m_ambientReduction = m_diffuseReduction = lightIntensity;

	m_testBillboard.GetMaterial().SetAmbientReduction(m_ambientReduction);
	m_terrain.SetAmbientReduction(m_ambientReduction);
	m_model.GetMaterial().SetAmbientReduction(m_ambientReduction);
	m_terrain.SetDiffuseReduction(m_diffuseReduction);
	m_model.GetMaterial().SetDiffuseReduction(m_ambientReduction);
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
	//
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
	m_model.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light);

	for (const auto& model : m_sceneModels) {
		model.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light);
	}

	m_testObject.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light);

	m_testBillboard.Render(m_shaderLib.GetShader("SphericalBillboard"), m_light, m_cameraController.GetCamera());

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
	m_model.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light, clipPlane);
	m_testObject.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light, clipPlane);

	m_testBillboard.Render(m_shaderLib.GetShader("SphericalBillboard"), m_light, m_cameraController.GetCamera());

	m_terrain.Render(m_shaderLib.GetShader("TerrainMaterial"), m_light, clipPlane);
}
