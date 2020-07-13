#ifndef JASS_KEYEVENT_H
#define JASS_KEYEVENT_H

#include "Event.h"

namespace Jass {

	class JASS_API KeyEvent : public Event {

	public:
		inline int GetKeyCode() const { return m_keycode; }

		// Inherited via Event

		virtual int GetCategoryFlags() const override {
			return (int)EventCategory::EventCategoryKeyboard | (int)EventCategory::EventCategoryInput;
		}

	protected:
		KeyEvent(int keycode) :
			m_keycode(keycode) {}

		int m_keycode;

	};

}

#endif // !JASS_KEYEVENT_H