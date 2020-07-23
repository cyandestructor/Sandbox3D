#include "jasspch.h"
#include "WinInput.h"

#include <GLFW/glfw3.h>

#include "Jass/Application.h"

namespace Jass {

	std::unique_ptr<Input> Input::s_instance = std::make_unique<WinInput>();

	bool WinInput::IntIsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int status = glfwGetKey(window, keycode);
		return (status == GLFW_PRESS) || (status == GLFW_RELEASE);
	}

	bool WinInput::IntIsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int status = glfwGetMouseButton(window, button);
		return status == GLFW_PRESS;
	}

	std::pair<float, float> WinInput::IntGetMousePos()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

}