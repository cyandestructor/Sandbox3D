#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Model.h"
#include "Collisions/CollisionBox3D.h"

class GameObject {

public:
	GameObject() = default;
	GameObject(const std::string& filename);
	GameObject(const std::string& filename, const CollisionBox3D& collisionBox);

	void LoadModel(const std::string& filename);
	void SetCollisionBox(float width, float height, float depth);

	bool HasCollisionBox() const { return m_collisionBox != nullptr; }

	void OnUpdate(Jass::Timestep ts);

	void Render(Jass::Ref<Jass::Shader>& shader, const Light& light, const Jass::JVec4& clipPlane = Jass::JVec4(0.0f)) const;

	const Jass::Ref<Model>& GetModel() const { return m_model; }
	Jass::Ref<Model>& GetModel() { return m_model; }

	const Jass::Ref<CollisionBox3D>& GetCollisionBox() const { return m_collisionBox; }
	Jass::Ref<CollisionBox3D>& GetCollisionBox() { return m_collisionBox; }

private:
	Jass::Ref<Model> m_model;
	Jass::Ref<CollisionBox3D> m_collisionBox;

};

#endif // !GAME_OBJECT_H
