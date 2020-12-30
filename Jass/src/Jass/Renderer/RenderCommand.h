#ifndef RENDER_COMMAND_H_JASS
#define RENDER_COMMAND_H_JASS

#include "RendererAPI.h"

namespace Jass {

	class JASS_API RenderCommand {

	public:
		inline static void Init()
		{
			s_rendererAPI->Init();
		}

		inline static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
		{
			s_rendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const JVec4& color)
		{
			s_rendererAPI->SetClearColor(color);
		}
		
		inline static void EnableDepthMask(bool enable)
		{
			s_rendererAPI->EnableDepthMask(enable);
		}

		inline static void Clear()
		{
			s_rendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, unsigned int indexCount = 0)
		{
			s_rendererAPI->DrawIndexed(vertexArray, indexCount);
		}

	private:
		static std::unique_ptr<RendererAPI> s_rendererAPI;

	};

}

#endif // !RENDER_COMMAND_H_JASS
