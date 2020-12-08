#include "Model.h"

#include "ModelLoader.h"

Model::Model()
{
}

Model::Model(const std::string& filename)
{
	Load(filename);
}

void Model::Load(const std::string& filename)
{
	m_mesh = ModelLoader::LoadFromFile(filename);
}

void Model::Render(Jass::Ref<Jass::Shader>& shader, const Light& light) const
{
	m_material.Prepare(shader, light);
	Jass::Renderer::Submit(shader, m_mesh.GetVertexArray(), m_transformation);
}
