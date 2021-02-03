#ifndef TRANSFORMATIONS_EXAMPLE_H
#define TRANSFORMATIONS_EXAMPLE_H

#include <Jass.h>

#include "../../Sandbox3D/Model/Model.h"

class Transformations : public Jass::Layer {

public:

	Transformations();
	
	virtual ~Transformations() = default;

	virtual void OnAttach() override;

	virtual void OnDetach() override;

	virtual void OnImGuiRender() override;

	virtual void OnUpdate(Jass::Timestep ts) override;

	virtual void OnEvent(Jass::Event& e) override;

private:
	Jass::PerspectiveCamera m_camera;

	float m_cameraRotation;

	Model m_model;

	Jass::JVec3 m_modelPosition;
	Jass::JVec3 m_modelScale;
	Jass::JVec3 m_modelRotation;

	Jass::JVec4 m_modelColor;
	float m_modelReflectivity;
	float m_modelShineDamper;

	Light m_light;
	
	Jass::ShaderLibrary m_shaderLib;

	void LoadShaders();
	void LoadModels();

	void UpdateModel();
	void UpdateCamera(Jass::Timestep ts);

	bool OnKeyPressedEvent(Jass::KeyPressedEvent& e);
	bool OnWindowResizeEvent(Jass::WindowResizeEvent& e);

};

#endif // !TRANSFORMATIONS_EXAMPLE_H
