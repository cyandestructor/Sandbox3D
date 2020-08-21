#include "jasspch.h"
#include "OpenGLRendererDebugOutput.h"

#include <glad/glad.h>

namespace Jass {

	const char* SourceToString(GLenum source)
	{
		switch (source)
		{
			case GL_DEBUG_SOURCE_API:
				return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				return "WINDOW SYSTEM";
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				return "SHADER COMPILER";
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				return "THIRD PARTY";
			case GL_DEBUG_SOURCE_APPLICATION:
				return "APPLICATION";
			case GL_DEBUG_SOURCE_OTHER:
				return "OTHER";
			default:
				return "UNKNOWN";
		}
	}

	const char* TypeToString(GLenum type)
	{
		switch (type)
		{
			case GL_DEBUG_TYPE_ERROR:
				return "ERROR";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				return "DEPRECATED BEHAVIOR";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				return "UDEFINED BEHAVIOR";
			case GL_DEBUG_TYPE_PORTABILITY:
				return "PORTABILITY";
			case GL_DEBUG_TYPE_PERFORMANCE:
				return "PERFORMANCE";
			case GL_DEBUG_TYPE_OTHER:
				return "OTHER";
			case GL_DEBUG_TYPE_MARKER:
				return "MARKER";
			default:
				return "UNKNOWN";
		}
	}

	void GLAPIENTRY GLDebugMessageCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* msg,
		const void* data)
	{
		switch (severity) {
			case GL_DEBUG_SEVERITY_HIGH:
				JASS_CORE_ERR("OpenGL Error {0}: {1} from {2}: {3}", id, TypeToString(type), SourceToString(source), msg);
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				JASS_CORE_WARN("OpenGL Error {0}: {1} from {2}: {3}", id, TypeToString(type), SourceToString(source), msg);
				break;
			case GL_DEBUG_SEVERITY_LOW:
				JASS_CORE_INFO("OpenGL Error {0}: {1} from {2}: {3}", id, TypeToString(type), SourceToString(source), msg);
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				JASS_CORE_TRACE("OpenGL Error {0}: {1} from {2}: {3}", id, TypeToString(type), SourceToString(source), msg);
				break;
			default:
				JASS_CORE_TRACE("OpenGL Error {0}: {1} from {2}: {3}", id, TypeToString(type), SourceToString(source), msg);
				break;
		}
	}

	void Jass::OpenGLRendererDebugOutput::Init()
	{
		JASS_CORE_ASSERT(glDebugMessageCallback, "The current OpenGL version does not support Debug");

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(GLDebugMessageCallback, nullptr);
		GLuint unusedIds = 0;
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
	}

}
