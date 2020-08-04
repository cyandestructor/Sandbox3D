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
		const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("v_viewProjection", sceneData->ViewProjectionMatrix);
		RenderCommand::DrawIndexed(vertexArray);
	}

}
