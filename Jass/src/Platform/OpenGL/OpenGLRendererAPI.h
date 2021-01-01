#ifndef OPENGL_RENDERER_API_H_JASS
#define OPENGL_RENDERER_API_H_JASS

#include "Jass/Renderer/RendererAPI.h"

namespace Jass {

	class JASS_API OpenGLRendererAPI : public RendererAPI {

	public:
		virtual void Init() override;

		virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;

		virtual void SetClearColor(const JVec4& color) override;
		virtual void Clear() override;

		virtual void EnableDepthMask(bool enable) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, unsigned int indexCount = 0, RenderMode renderMode = RenderMode::Triangle) override;

	};

}

#endif // !OPENGL_RENDERER_API_H_JASS
