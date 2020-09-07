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
		virtual void OnEvent(Event& e) override;

		void BlockEvents(bool block) { m_blockEvents = block; }

		void Begin();
		void End();

	private:
		bool m_blockEvents = false;

	};

}

#endif // !JASS_IMGUILAYER_H
