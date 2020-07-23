#include "jasspch.h"
#include "Application.h"

#include "Jass/Events/EventDispatcher.h"

// TEMPORARY
#include <glad/glad.h>

namespace Jass {

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		JASS_CORE_ASSERT(!s_instance, "Application already exists");
		s_instance = this;
		m_window = std::unique_ptr<IWindow>(IWindow::Create());
		m_window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		JASS_CORE_TRACE("{0}", e);

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend();) {
			// Pass the event though the layers
			(*it++)->OnEvent(e);
			// Stop when the event has been handled
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layer->OnAttach();
		m_layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		layer->OnAttach();
		m_layerStack.PushOverlay(layer);
	}

	void Application::Run()
	{
		while (m_isRunning) {

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_layerStack)
				layer->OnUpdate();

			m_window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_isRunning = false;
		return true;
	}
}
