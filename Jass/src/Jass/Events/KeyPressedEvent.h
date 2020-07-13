#ifndef JASS_KEYPRESSEDEVENT_H
#define JASS_KEYPRESSEDEVENT_H

#include "KeyEvent.h"

namespace Jass {

	class JASS_API KeyPressedEvent : public KeyEvent {

	public:
		KeyPressedEvent(int keycode, int repeatCount) :
			KeyEvent(keycode), m_repeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_repeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressed: " << m_keycode << " Repeat count: " << m_repeatCount;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_repeatCount;

	};

}

#endif // !JASS_KEYPRESSEDEVENT_H
