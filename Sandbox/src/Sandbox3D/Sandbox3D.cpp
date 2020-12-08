#include "Sandbox3D.h"

Sandbox3D::Sandbox3D()
	: m_light({ 0.0f, 0.0f, 200.0f }, { 1.0f,1.0f,1.0f,1.0f })
{
	m_shaderLib.Load("BasicMaterial", "assets/shaders/BasicMaterial.glsl");
}

void Sandbox3D::OnAttach()
{
	m_model.Load("assets/models/sphere.obj");
	m_model.GetMaterial().SetDiffuseTexture("assets/textures/Sandbox3D/Earth/earth-map.jpg");

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
	m_shaderLib.GetShader("BasicMaterial")->Bind();
	m_shaderLib.GetShader("BasicMaterial")->SetFloat3("u_cameraPosition", m_cameraController.GetCamera().GetPosition());
	m_model.Render(m_shaderLib.GetShader("BasicMaterial"), m_light);
	Jass::Renderer::EndScene();
}

void Sandbox3D::OnEvent(Jass::Event& e)
{
	m_cameraController.OnEvent(e);
}
