#ifndef SCENE_H_JASS
#define SCENE_H_JASS

#include "Jass/Core/Core.h"
#include "entt.hpp"

namespace Jass {

	class JASS_API Scene {

	public:
		Scene();

	private:
		entt::registry m_registry;

	};

}

#endif // !SCENE_H_JASS
