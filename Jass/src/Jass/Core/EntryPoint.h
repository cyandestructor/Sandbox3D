#ifndef JASS_ENTRYPOINT_H
#define JASS_ENTRYPOINT_H

#ifdef JASS_PLATFORM_WINDOWS

extern Jass::Application* Jass::CreateApplication();

int main(int argc, char** argv) {

	JASS_CORE_TRACE("Welcome to Jass");

	JASS_PROFILE_BEGIN_SESSION("Startup", "Jass_Startup.json");
	auto app = Jass::CreateApplication();
	JASS_PROFILE_END_SESSION();
	
	JASS_PROFILE_BEGIN_SESSION("Runtime", "Jass_Runtime.json");
	app->Run();
	JASS_PROFILE_END_SESSION();
	
	JASS_PROFILE_BEGIN_SESSION("Shutdown", "Jass_Shutdown.json");
	delete app;
	JASS_PROFILE_END_SESSION();

}

#endif

#endif