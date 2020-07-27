#ifndef JASS_OPENGLCONTEXT_H
#define JASS_OPENGLCONTEXT_H

#include "Jass/Renderer/IRenderContext.h"

struct GLFWwindow;

namespace Jass {

	class JASS_API OpenGLContext : public IRenderContext {

	public:
		OpenGLContext(GLFWwindow* windowHandler);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_windowHandler;

	};

}

#endif // !JASS_OPENGLCONTEXT_H
