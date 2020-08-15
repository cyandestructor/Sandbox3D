#ifndef JASS_APPLICATION_H
#define JASS_APPLICATION_H

#include "Core.h"
#include "IWindow.h"
#include "Jass/Events/ApplicationEvents.h"
#include "LayerStack.h"

namespace Jass {
	
	class ImGuiLayer;

	class JASS_API Application
	{
	public:
		Application();
		virtual ~Application();

		static Application& Get() { return *s_instance; }
		inline IWindow& GetWindow() { return *m_window; }

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Run();

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		static Application* s_instance;

		std::unique_ptr<IWindow> m_window;

		ImGuiLayer* m_imGuiLayer;
		bool m_isRunning = true;
		bool m_isMinimized = false;
		LayerStack m_layerStack;

	};

	//Must be defined in client
	Application* CreateApplication();

}

#endif