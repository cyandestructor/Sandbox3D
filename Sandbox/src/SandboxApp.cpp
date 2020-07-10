#include "Jass.h"

class Sandbox : public Jass::Application {

public:
	Sandbox() {

	}

	~Sandbox() {

	}

};

Jass::Application* Jass::CreateApplication() {
	return new Sandbox();
}