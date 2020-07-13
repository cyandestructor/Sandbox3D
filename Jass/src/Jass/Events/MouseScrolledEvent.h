#ifndef JASS_MOUSESCROLLEDEVENT_H
#define JASS_MOUSESCROLLEDEVENT_H

#include "Event.h"

namespace Jass {

	class JASS_API MouseScrolledEvent :public Event {

	public:
		MouseScrolledEvent(float xOffset, float yOffset) :
			m_xOffset(xOffset), m_yOffset(yOffset) {}

		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }

		// Inherited via Event

		virtual int GetCategoryFlags() const override {
			return (int)EventCategory::EventCategoryMouse | (int)EventCategory::EventCategoryInput;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolled " << m_xOffset << ", " << m_yOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)

	private:
		float m_xOffset, m_yOffset;

	};

}

#endif // !JASS_MOUSESCROLLEDEVENT_H
