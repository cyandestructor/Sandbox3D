#include "jasspch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "Shaders/Shader.h"

namespace Jass {

	struct Renderer2DStorage {
		// TODO: Change Ref with Scope
		Ref<Shader> Shader;
		Ref<VertexArray> VertexArray;
	};

	static Renderer2DStorage* s_storage;

	void Renderer2D::Init()
	{
		s_storage = new Renderer2DStorage;

		s_storage->Shader = Jass::Shader::Create("assets/shaders/FlatColor.glsl");

		float positions[] = {
			-0.5f, -0.5f, 0.0f,	// 0
			0.5f, -0.5f, 0.0f,	// 1
			0.5f, 0.5f, 0.0f,	// 2
			-0.5f, 0.5f, 0.0f	// 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		s_storage->VertexArray = Jass::VertexArray::Create();

		auto vertexBuffer = Jass::VertexBuffer::Create({ positions,sizeof(positions),Jass::DataUsage::StaticDraw });
		vertexBuffer->SetLayout({
			Jass::BufferElement(Jass::ShaderDataType::Float3,"position")
			});

		s_storage->VertexArray->AddVertexBuffer(vertexBuffer);

		auto indexBuffer = Jass::IndexBuffer::Create({ indices,6,Jass::DataUsage::StaticDraw });

		s_storage->VertexArray->SetIndexBuffer(indexBuffer);
	}

	void Renderer2D::Shutdown()
	{
		delete s_storage;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_storage->Shader->SetMat4("u_viewProjection", camera.GetViewProjection());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const JVec2& position, const JVec2& scale, const JVec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, 0.0f, scale, color);
	}

	void Renderer2D::DrawQuad(const JVec3& position, const JVec2& scale, const JVec4& color)
	{
		DrawQuad(position, 0.0f, scale, color);
	}

	void Renderer2D::DrawQuad(const JVec2& position, float rotation, const JVec2& scale, const JVec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, rotation, scale, color);
	}

	void Renderer2D::DrawQuad(const JVec3& position, float rotation, const JVec2& scale, const JVec4& color)
	{
		s_storage->Shader->Bind();
		s_storage->Shader->SetFloat4("u_color", color);

		JMat4 transformation = Translate(JMat4(1.0f), position);
		transformation = Rotate(transformation, Radians(rotation), { 0.0f,0.0f,1.0f });
		transformation = Scale(transformation, { scale.x, scale.y, 1.0f });
		s_storage->Shader->SetMat4("u_transformation", transformation);

		RenderCommand::DrawIndexed(s_storage->VertexArray);
	}

}
