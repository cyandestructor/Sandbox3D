#include "jasspch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Jass {
	
	// TEMPORARY
	std::unique_ptr<Renderer::SceneData> Renderer::sceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		sceneData->ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, 
		const Ref<VertexArray>& vertexArray,
		const JMat4& transformation)
	{
		shader->Bind();
		// Temporary
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_viewProjection", sceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_transformation", transformation);
		RenderCommand::DrawIndexed(vertexArray);
	}

}
