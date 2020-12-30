#include "Skybox.h"

Skybox::Skybox()
{
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	//m_texture = Jass::Texture3D::Create(filenames);

	m_vertexArray = Jass::VertexArray::Create();

	auto vbo = Jass::VertexBuffer::Create({ skyboxVertices, sizeof(skyboxVertices), Jass::DataUsage::StaticDraw });
	vbo->SetLayout({
		Jass::BufferElement(Jass::ShaderDataType::Float3,"a_position")
		});

	m_vertexArray->AddVertexBuffer(vbo);
}

void Skybox::SetTexture(const std::vector<std::string>& filenames)
{
	m_texture = Jass::Texture3D::Create(filenames);
}

void Skybox::SetCamera(const Jass::Camera& camera)
{
	m_shader->Bind();
	const auto& view = camera.GetView();
	const auto& projection = camera.GetProjection();
	m_shader->SetMat4("u_viewProjection", projection * Jass::JMat4(Jass::JMat3(view)));
	//m_shader->SetMat4("u_transformation", Jass::Scale(Jass::JMat4(1.0f), { 100.0f,100.0f,100.0f }));
}

void Skybox::Render()
{
	if (m_shader)
	{
		Jass::RenderCommand::EnableDepthMask(false);
		m_shader->Bind();
		m_texture->Bind();
		//m_shader->SetInt("u_texture", 0);
		Jass::RenderCommand::DrawIndexed(m_vertexArray, 36);
		//Jass::Renderer::Submit(m_shader, m_vertexArray, Jass::Scale(Jass::JMat4(1.0f), { 800.0f, 800.0f,800.0f }));
		Jass::RenderCommand::EnableDepthMask(true);
	}
}
