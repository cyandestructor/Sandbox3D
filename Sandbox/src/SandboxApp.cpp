#include <Jass.h>
#include <Jass/Core/EntryPoint.h>

//#include "Sandbox2D.h"
#include "Sandbox3D/Sandbox3D.h"

class Sandbox : public Jass::Application {

public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox3D());
	}

	~Sandbox() {

	}

};

Jass::Application* Jass::CreateApplication() {
	return new Sandbox();
}