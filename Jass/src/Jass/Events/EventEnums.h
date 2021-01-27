#ifndef JASS_EVENTENUMS_H
#define JASS_EVENTENUMS_H

#include "Jass/Core/Core.h"

namespace Jass {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		JoystickConnection
	};

	enum class EventCategory
	{
		None = 0,
		EventCategoryInput =			BIT(0),
		EventCategoryKeyboard =			BIT(1),
		EventCategoryMouse =			BIT(2),
		EventCategoryMouseButton =		BIT(3),
		EventCategoryApplication =		BIT(4)
	};

}

#endif // !JASS_EVENTENUMS_H
