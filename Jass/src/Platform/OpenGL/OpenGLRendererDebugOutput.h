#ifndef OPENGL_RENDERER_DEBUG_OUTPUT_H
#define OPENGL_RENDERER_DEBUG_OUTPUT_H

#include "Jass/Debug/IRendererDebugOutput.h"

namespace Jass {

	class OpenGLRendererDebugOutput : public IRendererDebugOutput {

	public:
		virtual ~OpenGLRendererDebugOutput() = default;

		virtual void Init();

	};

}

#endif // !OPENGL_RENDERER_DEBUG_OUTPUT_H
