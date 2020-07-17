#ifndef JASS_IWINDOW_H
#define JASS_IWINDOW_H

#include "jasspch.h"
#include "Core.h"
#include "Events/Event.h"

namespace Jass {

	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Jass Engine",
			unsigned int width = 1280, unsigned height = 720) :
			Title(title), Width(width), Height(height) {}

	};

	class JASS_API IWindow {

	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~IWindow() {}

		virtual void OnUpdate() = 0;
		
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallBack(const EventCallbackFn& eventCallback) = 0;
		virtual void SetVSync(bool enable) = 0;
		virtual bool IsVSync() const = 0;

		static IWindow* Create(const WindowProps& properties = WindowProps());

	};

}

#endif // !JASS_IWINDOW_H
