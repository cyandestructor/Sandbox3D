#include "jasspch.h"
#include "Renderer.h"

namespace Jass {
	
	// TEMPORARY
	std::unique_ptr<Renderer::SceneData> Renderer::sceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::BeginScene(const Camera& camera)
	{
		sceneData->ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, 
		const std::shared_ptr<VertexArray>& vertexArray,
		const glm::mat4& transformation)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_viewProjection", sceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_transformation", transformation);
		RenderCommand::DrawIndexed(vertexArray);
	}

}
