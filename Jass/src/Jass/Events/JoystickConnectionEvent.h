#ifndef JOYSTICK_CONNECTION_EVENT_JASS
#define JOYSTICK_CONNECTION_EVENT_JASS

#include "Event.h"
#include "Jass/Core/Joystick.h"

namespace Jass {

	class JASS_API JoystickConnectionEvent : public Event {

	public:
		JoystickConnectionEvent(Joystick joystick, bool connection)
			:m_joystick(joystick), m_connection(connection) {}

		Joystick GetJoystick() const { return m_joystick; }
		bool IsConnected() const { return m_connection; }

		virtual int GetCategoryFlags() const override {
			return (int)EventCategory::EventCategoryInput;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Joystick " << (int)m_joystick + 1 << (m_connection ? " connected" : " disconnected");
			return ss.str();
		}

		EVENT_CLASS_TYPE(JoystickConnection)

	private:
		Joystick m_joystick;
		bool m_connection;

	};

}

#endif // !JOYSTICK_CONNECTION_EVENT_JASS