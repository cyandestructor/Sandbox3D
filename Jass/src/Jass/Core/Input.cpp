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

}

#else
	#error Input only support Windows
#endif