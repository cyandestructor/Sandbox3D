#include "jasspch.h"
#include "Scene.h"

#include "Jass/ECS/Components/Components.h"
#include "Jass/ECS/Entity.h"
#include "Jass/Renderer/Renderer2D.h"

namespace Jass {

	Scene::Scene()
	{
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_registry.group<TransformationComponent>(entt::get<SpriteComponent>);

		for (auto entity : group) {
			auto& [transformation, sprite] = group.get<TransformationComponent, SpriteComponent>(entity);
			Renderer2D::DrawQuad(transformation, sprite.Color);
		}
	}

	Entity Scene::CreateEntity(const std::string& tag)
	{
		Entity entity = { m_registry.create(), this };
		// Every Entity has a transformation and tag by default
		entity.AddComponent<TransformationComponent>();
		entity.AddComponent<TagComponent>(tag.empty() ? "Entity" : tag);
		return entity;
	}

}
