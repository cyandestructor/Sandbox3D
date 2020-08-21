#ifndef IRENDERER_DEBUG_OUTPUT_H
#define IRENDERER_DEBUG_OUTPUT_H

namespace Jass {

	class IRendererDebugOutput {

	public:
		virtual ~IRendererDebugOutput() = default;

		virtual void Init() = 0;

	};

}

#endif // !IRENDERER_DEBUG_OUTPUT_H
