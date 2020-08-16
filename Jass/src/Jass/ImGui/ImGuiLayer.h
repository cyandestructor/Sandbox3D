#ifndef JASS_IMGUILAYER_H
#define JASS_IMGUILAYER_H

#include "Jass/Core/Layer.h"

namespace Jass {

	class JASS_API ImGuiLayer : public Layer {

	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnDetach() override;
		virtual void OnAttach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		float m_time = 0;

	};

}

#endif // !JASS_IMGUILAYER_H
