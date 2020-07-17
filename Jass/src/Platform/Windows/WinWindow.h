#ifndef JASS_WINWINDOW_H
#define JASS_WINWINDOW_H

#include "Jass/IWindow.h"
#include "GLFW/glfw3.h"

namespace Jass {

	class JASS_API WinWindow : public IWindow {

	public:
		WinWindow(const WindowProps& properties) {
			Init(properties);
		}
		virtual ~WinWindow() { Shutdown(); }
		
		// Inherited via IWindow
		
		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_windowData.Width; }
		
		inline unsigned int GetHeight() const override { return m_windowData.Height; }
		
		inline void SetEventCallBack(const EventCallbackFn& eventCallback) override {
			m_windowData.EventCallback = eventCallback;
		}
		
		inline void SetVSync(bool enable) override;
		
		inline bool IsVSync() const override { return m_windowData.VSync; }

	protected:
		virtual void Init(const WindowProps& properties);
		virtual void Shutdown();

	private:
		static bool s_glfwInitialized;

		GLFWwindow* m_window;

		struct WindowData {
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_windowData;

	};

}

#endif // !JASS_WINWINDOW_H
