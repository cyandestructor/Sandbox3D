#ifndef JASS_KEYRELEASEDEVENT_H
#define JASS_KEYRELEASEDEVENT_H

#include "KeyEvent.h"

namespace Jass {

	class JASS_API KeyReleasedEvent : public KeyEvent {

	public:
		KeyReleasedEvent(int keyCode) :
			KeyEvent(keyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleased: " << m_keycode;
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};

}

#endif // !JASS_KEYRELEASEDEVENT_H
