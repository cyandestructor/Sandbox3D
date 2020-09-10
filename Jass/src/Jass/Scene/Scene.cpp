#include "jasspch.h"
#include "Scene.h"

#include "Jass/ECS/Components/Components.h"
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

	entt::entity Scene::CreateEntity()
	{
		return m_registry.create();
	}

}
