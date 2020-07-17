#include "jasspch.h"
#include "Application.h"

#include "Jass/Events/ApplicationEvents.h"

namespace Jass {

	Application::Application()
	{
		m_window = std::unique_ptr<IWindow>(IWindow::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_isRunning) {
			m_window->OnUpdate();
		}
	}
}
