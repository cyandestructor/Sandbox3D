#ifndef JASS_LAYER_H
#define JASS_LAYER_H

#include "Core.h"
#include "Core/Timestep.h"
#include "Events/Events.h"

namespace Jass {

	class JASS_API Layer {

	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_debugName; }

	protected:
		std::string m_debugName;

	};

}

#endif // !JASS_LAYER_H
