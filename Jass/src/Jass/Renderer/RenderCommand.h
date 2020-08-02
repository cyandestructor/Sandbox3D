#ifndef RENDER_COMMAND_H_JASS
#define RENDER_COMMAND_H_JASS

#include "RendererAPI.h"

namespace Jass {

	class JASS_API RenderCommand {

	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_rendererAPI->SetClearColor(color);
		}
		
		inline static void Clear()
		{
			s_rendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_rendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static std::unique_ptr<RendererAPI> s_rendererAPI;

	};

}

#endif // !RENDER_COMMAND_H_JASS
