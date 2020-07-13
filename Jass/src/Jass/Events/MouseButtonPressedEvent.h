#ifndef JASS_MOUSEBUTTONPRESSEDEVENT_H
#define JASS_MOUSEBUTTONPRESSEDEVENT_H

#include "MouseButtonEvent.h"

namespace Jass {

	class JASS_API MouseButtonPressedEvent : public MouseButtonEvent {

	public:
		MouseButtonPressedEvent(int button) :
			MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressed (" << m_button << ")";
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)

	};

}

#endif // !JASS_MOUSEBUTTONPRESSEDEVENT_H
