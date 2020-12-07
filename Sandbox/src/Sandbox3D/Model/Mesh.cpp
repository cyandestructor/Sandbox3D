#include "Mesh.h"

Mesh::Mesh(const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices)
{
	m_vertexArray = Jass::VertexArray::Create();

	Jass::VertexBufferConfig vbConfig;
	vbConfig.Data = &vertices[0];
	vbConfig.Size = (unsigned int)vertices.size() * sizeof(MeshVertex);
	vbConfig.DataUsage = Jass::DataUsage::StaticDraw;
	Jass::Ref<Jass::VertexBuffer> vbo = Jass::VertexBuffer::Create(vbConfig);

	vbo->SetLayout({
		Jass::BufferElement(Jass::ShaderDataType::Float3,"a_position"),
		Jass::BufferElement(Jass::ShaderDataType::Float3,"a_normal"),
		Jass::BufferElement(Jass::ShaderDataType::Float2,"a_texCoords")
		});

	m_vertexArray->AddVertexBuffer(vbo);

	Jass::Ref<Jass::IndexBuffer> ibo = Jass::IndexBuffer::Create({ &indices[0], (unsigned int)indices.size(), Jass::DataUsage::StaticDraw });

	m_vertexArray->SetIndexBuffer(ibo);
}
