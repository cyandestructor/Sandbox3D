#include "jasspch.h"
#include "Application.h"

#include "Jass/Events/EventDispatcher.h"
#include "Jass/Renderer/Renderer.h"
#include "Jass/Renderer/Renderer2D.h"
#include "Jass/ImGui/ImGuiLayer.h"

// TEMPORARY
#include <GLFW/glfw3.h>

namespace Jass {

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		JASS_CORE_ASSERT(!s_instance, "Application already exists");
		s_instance = this;

		m_window = std::unique_ptr<IWindow>(IWindow::Create());
		m_window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
		Renderer2D::Init();

		m_imGuiLayer = new ImGuiLayer();
		PushOverlay(m_imGuiLayer);

	}

	Application::~Application()
	{
		Renderer2D::Shutdown();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

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

			static float lastime = 0;
			float time = (float)glfwGetTime();
			Timestep ts = time - lastime;
			lastime = time;

			if (!m_isMinimized) {
				for (Layer* layer : m_layerStack)
					layer->OnUpdate(ts);
			}

			m_imGuiLayer->Begin();
			for (Layer* layer : m_layerStack)
				layer->OnImGuiRender();
			m_imGuiLayer->End();

			m_window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_isRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		unsigned int width = e.GetWidth(), height = e.GetHeight();

		if (width == 0 || height == 0) {
			m_isMinimized = true;
			return false;
		}

		m_isMinimized = false;
		Renderer::OnWindowResize(width, height);

		return false;
	}

}
