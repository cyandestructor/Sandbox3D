#ifndef SCENE_H_JASS
#define SCENE_H_JASS

#include "Jass/Core/Timestep.h"
#include "entt.hpp"

namespace Jass {

	class Entity;

	class JASS_API Scene {

		friend class Entity;

	public:
		Scene();

		void OnUpdate(Timestep ts);

		Entity CreateEntity(const std::string& tag = std::string());

	private:
		entt::registry m_registry;

	};

}

#endif // !SCENE_H_JASS
