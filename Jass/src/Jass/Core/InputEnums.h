#ifndef INPUT_ENUMS_JASS
#define INPUT_ENUMS_JASS

#include "Jass/Core/Joystick.h"

namespace Jass {

	enum class CursorMode
	{
		Normal, Hidden, Disabled
	};

	enum class GamepadButton
	{
		A,
		B,
		X,
		Y,

		Cross = A,
		Circle = B,
		Square = X,
		Triangle = Y,

		LeftBumper,
		RightBumper,

		Back,
		Start,
		Guide,

		LeftThumb,
		RightThumb,

		DPadUp,
		DPadLeft,
		DPadDown,
		DPadRight
	};

	enum class GamepadAxis
	{
		LeftX,
		LeftY,

		RightX,
		RightY,

		LeftTrigger,
		RightTrigger
	};

}

#endif // !INPUT_ENUMS_JASS
