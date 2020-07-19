#include "jasspch.h"
#include "WinWindow.h"

#include "Jass/Events/Events.h"

namespace Jass {

	static void GLFWErrorCallback(int error, const char* description)
	{
		JASS_CORE_ERR("GLFW Error {0}: {1}", error, description);
	}

	IWindow* IWindow::Create(const WindowProps& properties)
	{
		return new WinWindow(properties);
	}

	bool WinWindow::s_glfwInitialized = false;

	void WinWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	inline void WinWindow::SetVSync(bool enable)
	{
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_windowData.VSync = enable;
	}

	void WinWindow::Init(const WindowProps& properties)
	{
		m_windowData.Title = properties.Title;
		m_windowData.Width = properties.Width;
		m_windowData.Height = properties.Height;

		JASS_CORE_INFO("Creating window. Title: {0}, {1} X {2} px",
			m_windowData.Title, m_windowData.Width, m_windowData.Height);

		if (!s_glfwInitialized) {

			int success = glfwInit();
			JASS_CORE_ASSERT(success, "Could not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_glfwInitialized = true;

		}

		m_window = glfwCreateWindow((int)m_windowData.Width, (int)m_windowData.Height,
			m_windowData.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_windowData);
		SetVSync(true);

		// Set the GLFW callbacks
		SetWindowEventCallbacks();
	}

	void WinWindow::Shutdown()
	{
		glfwDestroyWindow(m_window);
	}

	void WinWindow::SetWindowEventCallbacks()
	{
		SetWindowSizeCallback();
		SetWindowCloseCallback();
		SetWindowKeyCallback();
		SetWindowMouseButtonCallback();
		SetWindowMouseScrollCallback();
		SetWindowMouseMoveCallback();
	}

	void WinWindow::SetWindowSizeCallback()
	{
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent e(width, height);
			data.EventCallback(e);
			});

	}

	void WinWindow::SetWindowCloseCallback()
	{
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent e;
			data.EventCallback(e);
			});
	}

	void WinWindow::SetWindowKeyCallback()
	{
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, 0);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data.EventCallback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, 1);
					data.EventCallback(e);
					break;
				}
			}
			});
	}

	void WinWindow::SetWindowMouseButtonCallback()
	{
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data.EventCallback(e);
					break;
				}
			}

			});
	}

	void WinWindow::SetWindowMouseMoveCallback()
	{
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent e((float)x, (float)y);
			data.EventCallback(e);
			});
	}

	void WinWindow::SetWindowMouseScrollCallback()
	{
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent e((float)xOffset, (float)yOffset);
			data.EventCallback(e);

			});
	}

}