#ifndef JASS_APPLICATION_H
#define JASS_APPLICATION_H

#include "Core.h"
#include "IWindow.h"
#include "Jass/Events/ApplicationEvents.h"
#include "ImGui/ImGuiLayer.h"
#include "LayerStack.h"

// TEMPORARY
#include "Renderer/Shader.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

namespace Jass {
	
	class JASS_API Application
	{
	public:
		Application();
		virtual ~Application();

		static Application& Get() { return *s_instance; }
		inline IWindow& GetWindow() { return *m_window; }

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Run();

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		static Application* s_instance;

		std::unique_ptr<IWindow> m_window;

		ImGuiLayer* m_imGuiLayer;
		bool m_isRunning = true;
		LayerStack m_layerStack;

		//TEMPORARY
		unsigned int m_vertexArray;

		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
	};

	//Must be defined in client
	Application* CreateApplication();

}

#endif