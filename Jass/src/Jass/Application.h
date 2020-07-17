#ifndef JASS_APPLICATION_H
#define JASS_APPLICATION_H

#include "Core.h"
#include "IWindow.h"

namespace Jass {
	
	class JASS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<IWindow> m_window;
		bool m_isRunning = true;

	};

	//Must be defined in client
	Application* CreateApplication();

}

#endif