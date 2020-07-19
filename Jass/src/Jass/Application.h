#ifndef JASS_APPLICATION_H
#define JASS_APPLICATION_H

#include "Core.h"
#include "IWindow.h"
#include "Jass/Events/ApplicationEvents.h"

namespace Jass {
	
	class JASS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<IWindow> m_window;
		bool m_isRunning = true;

	};

	//Must be defined in client
	Application* CreateApplication();

}

#endif