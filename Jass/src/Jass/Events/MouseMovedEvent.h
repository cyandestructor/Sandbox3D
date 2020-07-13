#ifndef JASS_MOUSEMOVEDEVENT_H
#define JASS_MOUSEMOVEDEVENT_H

#include "Event.h"

namespace Jass {

	class JASS_API MouseMovedEvent : public Event {

	public:
		MouseMovedEvent(float x, float y) :
			m_mouseX(x), m_mouseY(y) {}

		inline float GetX() const { return m_mouseX; }
		inline float GetY() const { return m_mouseY; }

		// Inherited via Event

		virtual int GetCategoryFlags() const override {
			return (int)EventCategory::EventCategoryMouse | (int)EventCategory::EventCategoryInput;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMoved: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)

	private:
		float m_mouseX, m_mouseY;

	};

}

#endif // !JASS_MOUSEMOVEDEVENT_H
