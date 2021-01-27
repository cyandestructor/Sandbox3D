#ifndef JASS_INPUT_H
#define JASS_INPUT_H

#include "Core.h"
#include "InputEnums.h"

namespace Jass {

	class JASS_API Input {

	public:
		static bool IsKeyPressed(int keycode);

		static void SetCursorMode(CursorMode mode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePos();

		static bool IsGamepadConnected(Joystick gamepad);
		static std::string GetGamepadName(Joystick gamepad);
		static bool IsGamepadButtonPressed(Joystick gamepad, GamepadButton button);
		static float GetGamepadAxis(Joystick gamepad, GamepadAxis axis);

	};

}

#endif // !JASS_INPUT_H
