#ifndef JASS_ENTRYPOINT_H
#define JASS_ENTRYPOINT_H

#ifdef JASS_PLATFORM_WINDOWS

extern Jass::Application* Jass::CreateApplication();

int main(int argc, char** argv) {

	JASS_CORE_TRACE(Jass::SpdLogger, "Welcome to Jass");

	auto app = Jass::CreateApplication();
	app->Run();
	delete app;

}

#endif

#endif