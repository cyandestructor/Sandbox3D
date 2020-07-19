#ifndef JASS_MOUSEBUTTONRELEASEDEVENT_H
#define JASS_MOUSEBUTTONRELEASEDEVENT_H

#include "MouseButtonEvent.h"

namespace Jass {

	class JASS_API MouseButtonReleasedEvent : public MouseButtonEvent {

	public:
		MouseButtonReleasedEvent(int button) :
			MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleased (" << m_button << ")";

			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

	};

}

#endif // !JASS_MOUSEBUTTONPRESSEDEVENT_H
