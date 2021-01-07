#include "GameObject.h"

GameObject::GameObject(const std::string& filename)
{
	m_model = Jass::MakeRef<Model>(filename);
}

GameObject::GameObject(const std::string& filename, const CollisionBox3D& collisionBox)
{
	m_model = Jass::MakeRef<Model>(filename);
	m_collisionBox = Jass::MakeRef<CollisionBox3D>(collisionBox);
}

void GameObject::LoadModel(const std::string& filename)
{
	m_model = Jass::MakeRef<Model>(filename);
}

void GameObject::SetCollisionBox(float width, float height, float depth)
{
	if (m_model)
		m_collisionBox = Jass::MakeRef<CollisionBox3D>(m_model->GetPosition(), width, height, depth);
	else
		m_collisionBox = Jass::MakeRef<CollisionBox3D>(Jass::JVec3(0.0f), width, height, depth);
}

void GameObject::OnUpdate(Jass::Timestep ts)
{
	if (m_collisionBox && m_model)
		m_collisionBox->SetPosition(m_model->GetPosition());
}

void GameObject::Render(Jass::Ref<Jass::Shader>& shader, const Light& light, const Jass::JVec4& clipPlane) const
{
	if (m_model)
		m_model->Render(shader, light, clipPlane);
}
