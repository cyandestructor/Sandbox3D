#include "jasspch.h"
#include "WinWindow.h"

namespace Jass {

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
			s_glfwInitialized = true;

		}

		m_window = glfwCreateWindow((int)m_windowData.Width, (int)m_windowData.Height,
			m_windowData.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_windowData);
		SetVSync(true);
	}

	void WinWindow::Shutdown()
	{
		glfwDestroyWindow(m_window);
	}

}