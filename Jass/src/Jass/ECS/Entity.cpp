#include "jasspch.h"
#include "Entity.h"

namespace Jass {

	Entity::Entity(entt::entity handler, Scene* scene) :
		m_handler(handler), m_scene(scene)
	{
	}

}
