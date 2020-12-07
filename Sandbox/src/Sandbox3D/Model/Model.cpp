#include "Model.h"

#include "ModelLoader.h"

Model::Model()
{
	m_shader = Jass::Shader::Create("assets/shaders/FlatColor.glsl");
}

Model::Model(const std::string& filename)
{
	Load(filename);
	m_shader = Jass::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Model::Load(const std::string& filename)
{
	m_mesh = ModelLoader::LoadFromFile(filename);
}

void Model::Render() const
{
	m_shader->Bind();
	m_shader->SetFloat4("u_color", Jass::JVec4(0.8f, 0.3f, 0.2f, 1.0f));
	Jass::Renderer::Submit(m_shader, m_mesh.GetVertexArray(), m_transformation);
}
