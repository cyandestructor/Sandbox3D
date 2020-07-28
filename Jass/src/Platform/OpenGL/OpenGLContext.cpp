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

		JASS_CORE_INFO("OpenGL Info:");
		JASS_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		JASS_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		JASS_CORE_INFO("Version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandler);
	}

}
