#ifndef JASS_MOUSEBUTTONEVENT_H
#define JASS_MOUSEBUTTONEVENT_H

#include "Event.h"

namespace Jass {

	class JASS_API MouseButtonEvent : public Event {

	public:
		inline int GetButton() const { return m_button; }

		// Inherited via Event

		virtual int GetCategoryFlags() const override {
			return (int)EventCategory::EventCategoryMouseButton | (int)EventCategory::EventCategoryInput;
		}

	protected:
		MouseButtonEvent(int button) :
			m_button(button) {}

		int m_button;

	};

}

#endif // !JASS_MOUSEBUTTONEVENT_H
