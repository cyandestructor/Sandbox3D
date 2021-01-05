#include "Sandbox3D.h"

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
}

void Sandbox3D::OnAttach()
{
	std::vector<std::string> textures
	{
		"assets/textures/Sandbox3D/Skybox/right.png",
		"assets/textures/Sandbox3D/Skybox/left.png",
		"assets/textures/Sandbox3D/Skybox/top.png",
		"assets/textures/Sandbox3D/Skybox/bottom.png",
		"assets/textures/Sandbox3D/Skybox/front.png",
		"assets/textures/Sandbox3D/Skybox/back.png"
	};

	m_skybox.SetTexture(textures);

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
	m_terrain.SetAmbientReduction(0.6f);
	m_terrain.SetPosition({ -300.0f, 0.0f, 300.0f });

	m_model.Load("assets/models/sphere.obj");
	m_model.GetMaterial().SetDiffuseTexture("assets/textures/Sandbox3D/Dirt/dirt_color.jpg");
	m_model.GetMaterial().SetNormalTexture("assets/textures/Sandbox3D/Dirt/dirt_norm.jpg");
	m_model.SetPosition({ 0.0f, 70.0f, 0.0f });

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

void Sandbox3D::OnUpdate(Jass::Timestep ts)
{
	// Close the application
	if (Jass::Input::IsKeyPressed(JASS_KEY_ESCAPE))
		Jass::Application::Get().Close();

	FixCameraToTerrain();
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
	
	m_terrain.Render(m_shaderLib.GetShader("TerrainMaterial"), m_light, clipPlane);
}
