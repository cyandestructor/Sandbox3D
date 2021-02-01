#include <Jass.h>
#include <Jass/Core/EntryPoint.h>

#include "Sandbox3D/Sandbox3D.h"
#include "Examples/ModelLoading/ModelLoading.h"

class Sandbox : public Jass::Application {

public:
	Sandbox() {
		//PushLayer(new Sandbox3D());
		PushLayer(new ModelLoading);
	}

	~Sandbox() {

	}

};

Jass::Application* Jass::CreateApplication() {
	return new Sandbox();
}