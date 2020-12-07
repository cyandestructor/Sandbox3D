#include "Sandbox3D.h"

Sandbox3D::Sandbox3D()
{
}

void Sandbox3D::OnAttach()
{
	m_cube.Load("assets/models/sphere.obj");

	Jass::JMat4 transformation = m_cube.GetTransformation();
	Jass::Translate(transformation, { 0.0f, 0.0f,-30.0f });
	Jass::Scale(transformation, { 0.0001f, 0.0001f, 0.0001f });
	m_cube.SetTransformation(transformation);
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
	m_cube.Render();
	Jass::Renderer::EndScene();
}

void Sandbox3D::OnEvent(Jass::Event& e)
{
	m_cameraController.OnEvent(e);
}
