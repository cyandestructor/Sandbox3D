#include "jasspch.h"
#include "RendererDebugLog.h"

#include "Platform/OpenGL/OpenGLRendererDebugOutput.h"

namespace Jass {

	// TODO: CREATE DINAMICALLY FROM THE RENDERER API
	std::unique_ptr<IRendererDebugOutput> RendererDebugLog::s_debugOutput = std::make_unique<OpenGLRendererDebugOutput>();

	void RendererDebugLog::Init()
	{
		s_debugOutput->Init();
	}

}

