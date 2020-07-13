#ifndef JASS_ENTRYPOINT_H
#define JASS_ENTRYPOINT_H

#ifdef JASS_PLATFORM_WINDOWS

extern Jass::Application* Jass::CreateApplication();

int main(int argc, char** argv) {

	auto log = Jass::Log<Jass::SpdLogger>
		(std::make_shared<Jass::SpdLogger>(), std::make_shared<Jass::SpdLogger>());

	log.LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::INFO, "Welcome to Jass");
	log.LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::WARN, "Hello world");

	auto app = Jass::CreateApplication();
	app->Run();
	delete app;

}

#endif

#endif