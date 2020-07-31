#ifndef RENDERER_H_JASS
#define RENDERER_H_JASS

namespace Jass {

	enum class RendererAPI
	{
		None = 0, OpenGL
	};

	class JASS_API Renderer {

	public:
		inline static RendererAPI GetAPI() { return s_rendererAPI; }

	private:
		static RendererAPI s_rendererAPI;

	};

}

#endif // !RENDERER_H_JASS
