#ifndef RENDERER_API_H_JASS
#define RENDERER_API_H_JASS

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Jass {

	class JASS_API RendererAPI {

	public:
		enum class API
		{
			None = 0, OpenGL
		};

		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		static API GetAPI();

	private:
		static API s_API;

	};

}

#endif // !RENDERER_API_H_JASS
