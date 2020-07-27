#include "jasspch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Jass {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandler):
		m_windowHandler(windowHandler)
	{
		JASS_CORE_ASSERT(windowHandler, "The window handler is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandler);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JASS_CORE_ASSERT(status, "Could not initialize Glad");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandler);
	}

}
