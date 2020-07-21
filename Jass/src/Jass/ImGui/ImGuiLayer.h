#ifndef JASS_IMGUILAYER_H
#define JASS_IMGUILAYER_H

#include "Jass/Layer.h"

namespace Jass {

	class JASS_API ImGuiLayer : public Layer {

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate() override;
		void OnEvent(Event& e) override;
		void OnDetach() override;
		void OnAttach() override;

	private:
		float m_time = 0;

	};

}

#endif // !JASS_IMGUILAYER_H
