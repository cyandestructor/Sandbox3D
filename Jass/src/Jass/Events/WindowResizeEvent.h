#ifndef JASS_WINDOWRESIZEEVENT_H
#define JASS_WINDOWRESIZEEVENT_H

#include "Event.h"

namespace Jass {

	class JASS_API WindowResizeEvent : public Event {

	public:
		WindowResizeEvent(unsigned int width, unsigned int height) :
			m_wWidth(width), m_wHeight(height) {}

		inline unsigned int GetWidth() const { return m_wWidth; }
		inline unsigned int GetHeight() const { return m_wHeight; }

		virtual int GetCategoryFlags() const override {
			return (int)EventCategory::EventCategoryApplication;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResize: " << m_wWidth << ", " << m_wHeight;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)

	private:
		unsigned int m_wWidth, m_wHeight;

	};

}

#endif // !JASS_WINDOWRESIZEEVENT_H