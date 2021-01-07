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

void Skybox::AddTexture(const std::vector<std::string>& filenames, const std::string& uniformName, unsigned int slot)
{
	TextureInfo texture;
	texture.Texture = Jass::Texture3D::Create(filenames);
	texture.Name = uniformName;
	texture.Slot = slot;

	m_textures.push_back(texture);
}

void Skybox::Render(const Jass::Ref<Jass::Shader>& shader, const Jass::Camera& camera)
{
	Jass::RenderCommand::SetDepthFunction(Jass::DepthFunc::LessEqual);
	
	shader->Bind();
	// Set the camera
	auto view = camera.GetView();
	view = Jass::Rotate(view, Jass::Radians(m_rotation), { 0.0f, 1.0f, 0.0f });
	const auto& projection = camera.GetProjection();
	Jass::JMat4 viewProjection = projection * Jass::JMat4(Jass::JMat3(view));
	shader->SetMat4("u_viewProjection", viewProjection);

	m_texture->Bind();
	for (TextureInfo texture : m_textures) {
		texture.Texture->Bind(texture.Slot);
	}
	
	shader->SetInt("u_texture", m_firstTexture);
	shader->SetInt("u_texture2", m_secondTexture);
	shader->SetFloat("u_blendLevel", m_blendLevel);

	Jass::RenderCommand::DrawIndexed(m_vertexArray);
	
	Jass::RenderCommand::SetDepthFunction(Jass::DepthFunc::Less);
}
