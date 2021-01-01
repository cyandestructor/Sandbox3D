#ifndef RENDERER_API_H_JASS
#define RENDERER_API_H_JASS

#include "Jass/JMath/JMath.h"
#include "VertexArray.h"

namespace Jass {

	enum class RenderMode
	{
		Triangle, TriangleStrip
	};

	class JASS_API RendererAPI {

	public:
		enum class API
		{
			None = 0, OpenGL
		};

		virtual void Init() = 0;

		virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;

		virtual void SetClearColor(const JVec4& color) = 0;
		virtual void Clear() = 0;

		virtual void EnableDepthMask(bool enable) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, unsigned int indexCount = 0, RenderMode renderMode = RenderMode::Triangle) = 0;

		static API GetAPI();

	private:
		static API s_API;

	};

}

#endif // !RENDERER_API_H_JASS
