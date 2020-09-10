#ifndef SCENE_H_JASS
#define SCENE_H_JASS

#include "Jass/Core/Timestep.h"
#include "entt.hpp"

namespace Jass {

	class JASS_API Scene {

	public:
		Scene();

		void OnUpdate(Timestep ts);

		entt::entity CreateEntity();

		// Temporary
		entt::registry& GetReg() { return m_registry; }

	private:
		entt::registry m_registry;

	};

}

#endif // !SCENE_H_JASS
