#include "Sandbox3D.h"

Sandbox3D::Sandbox3D()
	: m_light({ 10.0f, 100.0f, 150.0f }, { 1.0f,1.0f,1.0f,1.0f }),
	m_terrain("assets/textures/Sandbox3D/heightmap.png", 300, 300, 3.0f)
{
	m_cameraController.GetCamera().SetProjection(60.0f, 1280.0f, 720.0f, 0.01f, 1000.0f);
	m_shaderLib.Load("BasicMaterial", "assets/shaders/BasicMaterial.glsl");
	m_shaderLib.Load("NormalsMaterial", "assets/shaders/NormalsMaterial.glsl");
	m_shaderLib.Load("TerrainMaterial", "assets/shaders/TerrainShader.glsl");
	m_shaderLib.Load("SkyboxShader", "assets/shaders/SkyboxShader.glsl");
	m_skybox.SetShader(m_shaderLib.GetShader("SkyboxShader"));
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
		"assets/textures/Sandbox3D/Skybox/back.png",
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

	m_model.Load("assets/models/sphere.obj");
	m_model.GetMaterial().SetDiffuseTexture("assets/textures/Sandbox3D/Dirt/dirt_color.jpg");
	m_model.GetMaterial().SetNormalTexture("assets/textures/Sandbox3D/Dirt/dirt_norm.jpg");

	Jass::JMat4 transformation = m_model.GetTransformation();
	Jass::Translate(transformation, { 0.0f, 0.0f,-30.0f });
	Jass::Scale(transformation, { 0.0001f, 0.0001f, 0.0001f });
	m_model.SetTransformation(transformation);
}

void Sandbox3D::OnDetach()
{
}

void Sandbox3D::OnUpdate(Jass::Timestep ts)
{
	m_cameraController.OnUpdate(ts);
	//FixCameraToTerrain();

	Jass::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
	Jass::RenderCommand::Clear();

	Jass::Renderer::BeginScene(m_cameraController.GetCamera());
	
	m_skybox.SetCamera(m_cameraController.GetCamera());
	m_skybox.Render();
	m_shaderLib.GetShader("NormalsMaterial")->Bind();
	m_shaderLib.GetShader("NormalsMaterial")->SetFloat3("u_cameraPosition", m_cameraController.GetCamera().GetPosition());
	m_model.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light);
	m_terrain.Render(m_shaderLib.GetShader("TerrainMaterial"), m_light);
	
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
