#ifndef RENDERER_H_JASS
#define RENDERER_H_JASS

#include "RenderCommand.h"
// TEMPORARY
#include "Shader.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"

namespace Jass {

	class JASS_API Renderer {

	public:
		static void Init();
		
		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,
			const Ref<VertexArray>& vertexArray,
			const glm::mat4& transformation = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		// TEMPORARY
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static std::unique_ptr<SceneData> sceneData;

	};

}

#endif // !RENDERER_H_JASS
