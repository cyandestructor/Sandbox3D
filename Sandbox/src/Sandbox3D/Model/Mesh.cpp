#include "Mesh.h"

Mesh::Mesh(std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices)
{
	CalculateTangentsBitangents(vertices);
	
	m_vertexArray = Jass::VertexArray::Create();

	Jass::VertexBufferConfig vbConfig;
	vbConfig.Data = &vertices[0];
	vbConfig.Size = (unsigned int)vertices.size() * sizeof(MeshVertex);
	vbConfig.DataUsage = Jass::DataUsage::StaticDraw;
	Jass::Ref<Jass::VertexBuffer> vbo = Jass::VertexBuffer::Create(vbConfig);

	vbo->SetLayout({
		Jass::BufferElement(Jass::ShaderDataType::Float3,"a_position"),
		Jass::BufferElement(Jass::ShaderDataType::Float3,"a_normal"),
		Jass::BufferElement(Jass::ShaderDataType::Float2,"a_texCoords"),
		Jass::BufferElement(Jass::ShaderDataType::Float3,"a_tangent"),
		Jass::BufferElement(Jass::ShaderDataType::Float3,"a_bitangent")
		});

	m_vertexArray->AddVertexBuffer(vbo);

	Jass::Ref<Jass::IndexBuffer> ibo = Jass::IndexBuffer::Create({ &indices[0], (unsigned int)indices.size(), Jass::DataUsage::StaticDraw });

	m_vertexArray->SetIndexBuffer(ibo);
}

void Mesh::CalculateTangentsBitangents(std::vector<MeshVertex>& vertices)
{
	for (size_t i = 0; i < vertices.size(); i += 3)
	{
		auto& v0 = vertices[i + 0].Position;
		auto& v1 = vertices[i + 1].Position;
		auto& v2 = vertices[i + 2].Position;

		auto& uv0 = vertices[i + 0].TexCoord;
		auto& uv1 = vertices[i + 1].TexCoord;
		auto& uv2 = vertices[i + 2].TexCoord;

		auto deltaPos1 = v1 - v0;
		auto deltaPos2 = v2 - v0;

		auto deltaUV1 = uv1 - uv0;
		auto deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

		auto tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
		auto bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

		vertices[i + 0].Tangent = tangent;
		vertices[i + 1].Tangent = tangent;
		vertices[i + 2].Tangent = tangent;

		vertices[i + 0].Bitangent = bitangent;
		vertices[i + 1].Bitangent = bitangent;
		vertices[i + 2].Bitangent = bitangent;
	}
}
