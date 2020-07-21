#include "Jass.h"

class ExampleLayer : public Jass::Layer {

public:
	
	ExampleLayer() :
		Layer("Example")
	{

	}

	void OnUpdate() override {
		JASS_LOG_INFO("ExampleClass::Update");
	}

	void OnEvent(Jass::Event& e) override {
		JASS_LOG_TRACE("{0}", e);
	}

};

class Sandbox : public Jass::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Jass::ImGuiLayer());
	}

	~Sandbox() {

	}

};

Jass::Application* Jass::CreateApplication() {
	return new Sandbox();
}