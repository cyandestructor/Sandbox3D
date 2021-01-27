#include "jasspch.h"
#include "Input.h"

#include "Jass/Core/Application.h"

#ifdef JASS_PLATFORM_WINDOWS

#include <GLFW/glfw3.h>

namespace Jass {

	bool Input::IsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int status = glfwGetKey(window, keycode);
		return (status == GLFW_PRESS) || (status == GLFW_REPEAT);
	}

	void Input::SetCursorMode(CursorMode mode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int modeValue;

		switch (mode)
		{
		case CursorMode::Normal:
			modeValue = GLFW_CURSOR_NORMAL;
			break;
		case CursorMode::Hidden:
			modeValue = GLFW_CURSOR_HIDDEN;
			break;
		case CursorMode::Disabled:
			modeValue = GLFW_CURSOR_DISABLED;
			break;
		default:
			JASS_CORE_ASSERT(false, "Unknown cursor mode");
			break;
		}

		glfwSetInputMode(window, GLFW_CURSOR, modeValue);
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int status = glfwGetMouseButton(window, button);
		return status == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePos()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	int ToGLFW(Joystick joystick)
	{
		return GLFW_JOYSTICK_1 + (int)joystick;
	}

	int ToGLFW(GamepadButton button)
	{
		int value = 0;
		switch (button)
		{
		case Jass::GamepadButton::A:
			value = GLFW_GAMEPAD_BUTTON_A;
			break;
		case Jass::GamepadButton::B:
			value = GLFW_GAMEPAD_BUTTON_B;
			break;
		case Jass::GamepadButton::X:
			value = GLFW_GAMEPAD_BUTTON_X;
			break;
		case Jass::GamepadButton::Y:
			value = GLFW_GAMEPAD_BUTTON_Y;
			break;
		case Jass::GamepadButton::LeftBumper:
			value = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER;
			break;
		case Jass::GamepadButton::RightBumper:
			value = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER;
			break;
		case Jass::GamepadButton::Back:
			value = GLFW_GAMEPAD_BUTTON_BACK;
			break;
		case Jass::GamepadButton::Start:
			value = GLFW_GAMEPAD_BUTTON_START;
			break;
		case Jass::GamepadButton::Guide:
			value = GLFW_GAMEPAD_BUTTON_GUIDE;
			break;
		case Jass::GamepadButton::LeftThumb:
			value = GLFW_GAMEPAD_BUTTON_LEFT_THUMB;
			break;
		case Jass::GamepadButton::RightThumb:
			value = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB;
			break;
		case Jass::GamepadButton::DPadUp:
			value = GLFW_GAMEPAD_BUTTON_DPAD_UP;
			break;
		case Jass::GamepadButton::DPadLeft:
			value = GLFW_GAMEPAD_BUTTON_DPAD_LEFT;
			break;
		case Jass::GamepadButton::DPadDown:
			value = GLFW_GAMEPAD_BUTTON_DPAD_DOWN;
			break;
		case Jass::GamepadButton::DPadRight:
			value = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT;
			break;
		default:
			JASS_CORE_ASSERT(false, "Unknown gamepad button");
			break;
		}

		return value;
	}

	int ToGLFW(GamepadAxis axis)
	{
		int value = 0;

		switch (axis)
		{
		case Jass::GamepadAxis::LeftX:
			value = GLFW_GAMEPAD_AXIS_LEFT_X;
			break;
		case Jass::GamepadAxis::LeftY:
			value = GLFW_GAMEPAD_AXIS_LEFT_Y;
			break;
		case Jass::GamepadAxis::RightX:
			value = GLFW_GAMEPAD_AXIS_RIGHT_X;
			break;
		case Jass::GamepadAxis::RightY:
			value = GLFW_GAMEPAD_AXIS_RIGHT_Y;
			break;
		case Jass::GamepadAxis::LeftTrigger:
			value = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER;
			break;
		case Jass::GamepadAxis::RightTrigger:
			value = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER;
			break;
		default:
			JASS_CORE_ASSERT(false, "Unknown gamepad axis");
			break;
		}

		return value;
	}

	bool Input::IsGamepadConnected(Joystick gamepad)
	{
		return glfwJoystickIsGamepad(ToGLFW(gamepad));
	}

	std::string Input::GetGamepadName(Joystick gamepad)
	{
		const char* name = nullptr;
		name = glfwGetGamepadName(ToGLFW(gamepad));

		if (name)
			return name;
		else
			return "";
	}

	bool Input::IsGamepadButtonPressed(Joystick gamepad, GamepadButton button)
	{
		GLFWgamepadstate state = { 0 };
		bool isPressed = false;

		if (glfwGetGamepadState(ToGLFW(gamepad), &state))
		{
			isPressed = state.buttons[ToGLFW(button)];
		}

		return isPressed;
	}

	float Input::GetGamepadAxis(Joystick gamepad, GamepadAxis axis)
	{
		GLFWgamepadstate state = { 0 };
		float value = 0.0f;

		if (glfwGetGamepadState(ToGLFW(gamepad), &state))
		{
			value = state.axes[ToGLFW(axis)];
		}

		return value;
	}

}

#else
	#error Input only support Windows
#endif