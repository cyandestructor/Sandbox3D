#include "Sandbox3D.h"

Sandbox3D::Sandbox3D()
	: m_light({ 0.0f, 0.0f, 200.0f }, { 1.0f,1.0f,1.0f,1.0f }),
	m_terrain("assets/textures/Sandbox3D/heightmap.png", 500, 500)
{
	m_cameraController.GetCamera().SetProjection(45.0f, 1280.0f, 720.0f, 0.1f, 800.0f);
	m_shaderLib.Load("BasicMaterial", "assets/shaders/BasicMaterial.glsl");
	m_shaderLib.Load("NormalsMaterial", "assets/shaders/NormalsMaterial.glsl");
	m_shaderLib.Load("TerrainMaterial", "assets/shaders/TerrainShader.glsl");
}

void Sandbox3D::OnAttach()
{
	m_terrain.AddTexture("assets/textures/Sandbox3D/Dirt/dirt_color.jpg", "u_diffuseTex", 1);
	
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

	Jass::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
	Jass::RenderCommand::Clear();

	Jass::Renderer::BeginScene(m_cameraController.GetCamera());
	m_terrain.Render(m_shaderLib.GetShader("TerrainMaterial"), m_light);
	m_shaderLib.GetShader("NormalsMaterial")->Bind();
	m_shaderLib.GetShader("NormalsMaterial")->SetFloat3("u_cameraPosition", m_cameraController.GetCamera().GetPosition());
	m_model.Render(m_shaderLib.GetShader("NormalsMaterial"), m_light);
	Jass::Renderer::EndScene();
}

void Sandbox3D::OnEvent(Jass::Event& e)
{
	m_cameraController.OnEvent(e);
}
