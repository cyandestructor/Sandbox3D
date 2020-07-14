#include "Application.h"

#include "Jass/Events/ApplicationEvents.h"
#include "Log.h"
#include "SpdLogger.h"

namespace Jass {

	Application::Application() {



	}

	Application::~Application() {



	}

	void Application::Run() {
	
		JASS_CORE_INFO(SpdLogger, "Hello world!");

		while (true);

	}
}
