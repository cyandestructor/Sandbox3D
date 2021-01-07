#include "Billboard.h"

Billboard::Billboard()
{
	static const float vertices[] = {
		 -0.5f, -0.5f, 0.0f,
		 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 1.0f, 0.0f,
		 -0.5f, 0.5f, 0.0f,
		 0.0f, 1.0f,
		 0.5f, 0.5f, 0.0f,
		 1.0f, 1.0f
	};

	m_vertexArray = Jass::VertexArray::Create();

	auto vbo = Jass::VertexBuffer::Create({ vertices, sizeof(vertices), Jass::DataUsage::StaticDraw });

	vbo->SetLayout({
		Jass::BufferElement(Jass::ShaderDataType::Float3, "a_position"),
		Jass::BufferElement(Jass::ShaderDataType::Float2, "a_texCoords")
		});

	m_vertexArray->AddVertexBuffer(vbo);

	unsigned int indices[] = {
		0, 1, 2,
		2, 1, 3
	};

	auto ibo = Jass::IndexBuffer::Create({ indices, 6, Jass::DataUsage::StaticDraw });

	m_vertexArray->SetIndexBuffer(ibo);

}

Billboard::Billboard(const Jass::JVec3& position, const Jass::JVec3& scale)
	:m_position(position), m_scale(scale)
{
	static const float vertices[] = {
		 -0.5f, -0.5f, 0.0f,
		 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 1.0f, 0.0f,
		 -0.5f, 0.5f, 0.0f,
		 0.0f, 1.0f,
		 0.5f, 0.5f, 0.0f,
		 1.0f, 1.0f
	};

	m_vertexArray = Jass::VertexArray::Create();

	auto vbo = Jass::VertexBuffer::Create({ vertices, sizeof(vertices), Jass::DataUsage::StaticDraw });

	vbo->SetLayout({
		Jass::BufferElement(Jass::ShaderDataType::Float3, "a_position"),
		Jass::BufferElement(Jass::ShaderDataType::Float2, "a_texCoords")
		});

	m_vertexArray->AddVertexBuffer(vbo);

	unsigned int indices[] = {
		0, 1, 2,
		2, 1, 3
	};

	auto ibo = Jass::IndexBuffer::Create({ indices, 6, Jass::DataUsage::StaticDraw });

	m_vertexArray->SetIndexBuffer(ibo);

}

void Billboard::Render(Jass::Ref<Jass::Shader>& shader, const Light& light, const Jass::Camera& camera)
{
	shader->Bind();
	const auto& viewMatrix = camera.GetView();
	Jass::JVec3 cameraRightWS = { viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0] };
	Jass::JVec3 cameraUpWS = { viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1] };
	shader->SetFloat3("u_cameraRightWS", cameraRightWS);
	shader->SetFloat3("u_cameraUpWS", cameraUpWS);
	shader->SetFloat3("u_billboardPosition", m_position);
	shader->SetFloat3("u_billboardScale", m_scale);

	shader->SetMat4("u_viewProjection", camera.GetViewProjection());
	m_material.Prepare(shader, light);
	Jass::RenderCommand::DrawIndexed(m_vertexArray);
	//Jass::Renderer::Submit(shader, m_vertexArray);
}
