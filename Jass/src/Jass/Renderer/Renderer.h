#ifndef RENDERER_H_JASS
#define RENDERER_H_JASS

#include "RenderCommand.h"

namespace Jass {

	class JASS_API Renderer {

	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};

}

#endif // !RENDERER_H_JASS
