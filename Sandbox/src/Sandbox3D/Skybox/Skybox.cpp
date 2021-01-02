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

	m_vertexArray = Jass::VertexArray::Create();

	auto vbo = Jass::VertexBuffer::Create({ skyboxVertices, sizeof(skyboxVertices), Jass::DataUsage::StaticDraw });
	vbo->SetLayout({
		Jass::BufferElement(Jass::ShaderDataType::Float3,"a_position")
		});

	m_vertexArray->AddVertexBuffer(vbo);

	unsigned int indices[36];

	for (unsigned int i = 0; i < 36; i++) {
		indices[i] = i;
	}

	auto ibo = Jass::IndexBuffer::Create({ indices, 36, Jass::DataUsage::StaticDraw });
	m_vertexArray->SetIndexBuffer(ibo);
}

void Skybox::SetTexture(const std::vector<std::string>& filenames)
{
	m_texture = Jass::Texture3D::Create(filenames);
}

void Skybox::Render(const Jass::Ref<Jass::Shader>& shader, const Jass::Camera& camera)
{
	Jass::RenderCommand::SetDepthFunction(Jass::DepthFunc::LessEqual);
	
	shader->Bind();
	// Set the camera
	const auto& view = camera.GetView();
	const auto& projection = camera.GetProjection();
	shader->SetMat4("u_viewProjection", projection * Jass::JMat4(Jass::JMat3(view)));

	m_texture->Bind();
	Jass::RenderCommand::DrawIndexed(m_vertexArray);
	
	Jass::RenderCommand::SetDepthFunction(Jass::DepthFunc::Less);
}
