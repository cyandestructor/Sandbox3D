#ifndef RENDERER_DEBUG_LOG
#define RENDERER_DEBUG_LOG

#include "IRendererDebugOutput.h"

namespace Jass {

	class RendererDebugLog {

	public:
		static void Init();

	private:
		static std::unique_ptr<IRendererDebugOutput> s_debugOutput;

	};

}

#endif // !RENDERER_DEBUG_LOG
