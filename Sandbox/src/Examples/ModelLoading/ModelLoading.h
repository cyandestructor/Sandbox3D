#ifndef MODEL_LOADING_EXAMPLE
#define MODEL_LOADING_EXAMPLE

// Include the Jass Engine Header file to access every feature
#include <Jass.h>

// Files for Models, Materials, Lights, and etcetera, are currently on the Sandbox3D folder
#include "../../Sandbox3D/Model/Model.h"

class ModelLoading : public Jass::Layer {

public:

	/*
		This is the contructor of the Layer.
		Some things should be initialized here. (Ex. Cameras, The Terrain)
	*/
	ModelLoading();
	
	virtual ~ModelLoading() = default;

	/*
		The OnAttach method is called when the layer is attached
		to the Layer Stack of the Application.
		You can use it for initializations.
	*/
	virtual void OnAttach() override;

	/*
		The OnDetach method is called when the Layer Stack is deleted,
		usually at the end of the application.
		You can use it for things you want to do before closing the program.
	*/
	virtual void OnDetach() override;

	/*
		The OnImGuiRender method is used to create GUI Dialogs.
		Jass Engine uses Dear ImGui library for that.
		Links to Dear ImGui
		Repo: https://github.com/ocornut/imgui
		Docs: https://github.com/ocornut/imgui/wiki
	*/
	virtual void OnImGuiRender() override;

	/*
		The OnUpdate method is the key method of the Game Loop.
		Do your Game Logic and Rendering here.
	*/
	virtual void OnUpdate(Jass::Timestep ts) override;

	/*
		The OnEvent method is used to Capture and Dispatch Events (ex. Keyboard, Mouse, Window...).
		Bind your Event Handler Methods here.
	*/
	virtual void OnEvent(Jass::Event& e) override;

private:
	// You need at least one camera to render
	Jass::PerspectiveCamera m_camera;

	float m_cameraRotation = 0.0f;

	// The model class for loading models. Each model object has a Mesh and a Material
	Model m_model;

	/*
		The Light class contains a position and a color.
		At least one light is needed for proper material rendering.
		Only one light on the scene is currently supported, but you can make
		some changes to support multiple light sources if you require.
	*/
	Light m_light;
	
	Jass::JVec3 m_lightPosition;
	Jass::JVec4 m_lightColor;

	// A Shader Library is an easy way to load and keep all the shaders you need
	Jass::ShaderLibrary m_shaderLib;

	void LoadShaders();
	void LoadModels();

	void UpdateCamera(Jass::Timestep ts);
	void UpdateLight();

	bool OnKeyPressedEvent(Jass::KeyPressedEvent& e);
	bool OnWindowResizeEvent(Jass::WindowResizeEvent& e);

};

#endif // !MODEL_LOADING_EXAMPLE
