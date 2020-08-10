#ifndef OPENGL_RENDERER_API_H_JASS
#define OPENGL_RENDERER_API_H_JASS

#include "Jass/Renderer/RendererAPI.h"

namespace Jass {

	class JASS_API OpenGLRendererAPI : public RendererAPI {

	public:
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	};

}

#endif // !OPENGL_RENDERER_API_H_JASS
