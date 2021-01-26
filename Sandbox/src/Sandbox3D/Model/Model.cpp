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

void Model::SetPosition(const Jass::JVec3& position)
{
	m_position = position;
	CalculateTransformation();
}

void Model::Rotate(const Jass::JVec3& axis, float angle)
{
	m_rotation = Jass::Rotate(m_rotation, Jass::Radians(angle), axis);
	CalculateTransformation();
}

void Model::SetScale(const Jass::JVec3& scale)
{
	m_scale = scale;
	CalculateTransformation();
}

void Model::Render(Jass::Ref<Jass::Shader>& shader, const Light& light, const Jass::JVec4& clipPlane) const
{
	m_material.Prepare(shader, light);
	shader->Bind();
	Jass::JMat4 normalMatrix = Jass::Transpose(Jass::Inverse(m_transformation));
	shader->SetMat4("u_normalMatrix", normalMatrix);
	shader->SetFloat4("u_clipPlane", clipPlane);
	Jass::Renderer::Submit(shader, m_mesh.GetVertexArray(), m_mesh.GetRenderMode(), m_transformation);
}

void Model::CalculateTransformation()
{
	m_transformation = Jass::Translate(Jass::JMat4(1.0f), m_position);
	m_transformation *= m_rotation;
	m_transformation = Jass::Scale(m_transformation, m_scale);
}
