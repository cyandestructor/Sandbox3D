#ifndef RENDERER_H_JASS
#define RENDERER_H_JASS

#include "RenderCommand.h"
#include "Shaders/ShaderLibrary.h"
#include "Jass/Camera/Camera.h"

namespace Jass {

	class JASS_API Renderer {

	public:
		static void Init();

		static void OnWindowResize(unsigned int width, unsigned int height);
		
		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,
			const Ref<VertexArray>& vertexArray,
			const JMat4& transformation = JMat4(1.0f));

		static void Submit(const Ref<Shader>& shader,
			const Ref<VertexArray>& vertexArray,
			RenderMode renderMode,
			const JMat4& transformation = JMat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		// TEMPORARY
		struct SceneData {
			JMat4 ViewProjectionMatrix;
		};

		static std::unique_ptr<SceneData> sceneData;

	};

}

#endif // !RENDERER_H_JASS
