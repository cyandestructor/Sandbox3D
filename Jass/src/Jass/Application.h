#ifndef JASS_APPLICATION_H
#define JASS_APPLICATION_H

#include "Core.h"

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