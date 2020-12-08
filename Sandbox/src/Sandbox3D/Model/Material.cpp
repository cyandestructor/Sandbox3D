#include "Material.h"

Material::Material()
{
	m_whiteTexture = Jass::Texture2D::Create(1, 1);
	uint32_t texData = 0xffffffff;
	m_whiteTexture->SetData(&texData, sizeof(uint32_t));
	m_whiteTexture->Bind(0);
}

void Material::SetDiffuseTexture(const std::string& textureFilename)
{
	m_diffuseTexture = Jass::Texture2D::Create(textureFilename);
}

void Material::Prepare(Jass::Ref<Jass::Shader>& shader, const Light& light) const
{
	shader->Bind();

	shader->SetFloat3("u_lightPosition", light.GetPosition());
	shader->SetFloat4("u_lightColor", light.GetColor());

	shader->SetFloat("u_ambientReduction", m_ambientReduction);
	shader->SetFloat("u_diffuseReduction", m_diffuseReduction);
	shader->SetFloat("u_reflectivity", m_reflectivity);
	shader->SetFloat("u_shineDamper", m_shineDamper);

	if (m_diffuseTexture) {
		m_diffuseTexture->Bind(1);
		shader->SetInt("u_diffuseTex", 1);
	}
	else
		shader->SetInt("u_diffuseTex", 0);

	shader->SetFloat4("u_color", m_color);
}
