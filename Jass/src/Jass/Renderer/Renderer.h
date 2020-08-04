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
		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader,
			const std::shared_ptr<VertexArray>& vertexArray);

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
