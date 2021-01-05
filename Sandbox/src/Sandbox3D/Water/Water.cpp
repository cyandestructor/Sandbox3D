#include "Water.h"

Water::Water(const Jass::JVec2& scale, unsigned int screenWidth, unsigned int screenHeight)
{
	Jass::FramebufferConfig fboConfig;
	fboConfig.Width = screenWidth;
	fboConfig.Height = screenHeight;

	m_reflectionFbo = Jass::Framebuffer::Create(fboConfig);
	m_refractionFbo = Jass::Framebuffer::Create(fboConfig);

	float quad[] = {
		-0.5f * scale.x, 0.0f, -0.5f * scale.y,
		0.0f, 1.0f,
		-0.5f * scale.x, 0.0f, 0.5f * scale.y,
		0.0f, 0.0f,
		0.5f * scale.x, 0.0f, -0.5f * scale.y,
		1.0f, 1.0f,
		0.5f * scale.x, 0.0f, 0.5f * scale.y,
		1.0f, 0.0f,
	};

	m_vertexArray = Jass::VertexArray::Create();

	auto vbo = Jass::VertexBuffer::Create({ quad, sizeof(quad), Jass::DataUsage::StaticDraw });

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

void Water::BeginReflection() const
{
	m_reflectionFbo->Bind();
	Jass::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
	Jass::RenderCommand::Clear();
}

void Water::EndReflection() const
{
	m_reflectionFbo->Unbind();
}

void Water::BeginRefraction() const
{
	m_refractionFbo->Bind();
	Jass::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
	Jass::RenderCommand::Clear();
}

void Water::EndRefraction() const
{
	m_refractionFbo->Unbind();
}

void Water::SetTextures(const std::string& dudv, const std::string& normal)
{
	m_dudvTexture = Jass::Texture2D::Create(dudv);
	m_normalTexture = Jass::Texture2D::Create(normal);
}

void Water::Render(const Jass::Ref<Jass::Shader>& shader, const Light& light, const Jass::Camera& camera) const
{
	shader->Bind();

	// Send information to the shader
	shader->SetFloat("u_tilingFactor", m_tilingFactor);
	shader->SetFloat4("u_color", m_color);

	shader->SetFloat("u_reflectivity", m_reflectivity);
	shader->SetFloat("u_shineDamper", m_shineDamper);

	shader->SetFloat3("u_lightPosition", light.GetPosition());
	shader->SetFloat4("u_lightColor", light.GetColor());

	shader->SetFloat("u_distortionFactor", m_distortionFactor);
	shader->SetFloat("u_motionFactor", m_motionFactor);

	shader->SetFloat3("u_cameraPosition", camera.GetPosition());

	// Bind textures and send samplers
	m_reflectionFbo->BindColorAttachment(0);
	shader->SetInt("u_reflection", 0);
	m_refractionFbo->BindColorAttachment(1);
	shader->SetInt("u_refraction", 1);
	
	if (m_dudvTexture) {
		m_dudvTexture->Bind(2);
		shader->SetInt("u_distortion", 2);
	}

	if (m_normalTexture) {
		m_normalTexture->Bind(3);
		shader->SetInt("u_normal", 3);
	}

	// Render
	Jass::JMat4 transformation = Jass::Translate(Jass::JMat4(1.0f), m_position);
	Jass::Renderer::Submit(shader, m_vertexArray, transformation);
}
