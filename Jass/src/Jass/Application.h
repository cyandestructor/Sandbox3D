#ifndef JASS_APPLICATION_H
#define JASS_APPLICATION_H

#include "Core.h"
#include "Jass/Events/ApplicationEvents.h"
#include "Log.h"
#include "SpdLogger.h"

namespace Jass {
	
	class JASS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//Must be defined in client
	Application* CreateApplication();

}

#endif