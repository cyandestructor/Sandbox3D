#ifndef JASS_KEYTYPEDEVENT_H
#define JASS_KEYTYPEDEVENT_H

#include "KeyEvent.h"

namespace Jass {

	class JASS_API KeyTypedEvent : public KeyEvent {

	public:
		KeyTypedEvent(int keycode) :
			KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTyped: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)

	};

}

#endif // !JASS_KEYTYPEDEVENT_H
