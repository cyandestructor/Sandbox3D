#include "Plane.h"

Mesh Plane::Generate()
{
	std::vector<MeshVertex> vertices;
	std::vector<unsigned int> indices;

	m_vertexCountW = m_widthDiv + 1;
	m_vertexCountD = m_depthDiv + 1;

	float stepX = (float)m_width / m_widthDiv;
	float stepZ = (float)m_depth / m_depthDiv;

	unsigned int totalCount = m_vertexCountD * m_vertexCountW;
	vertices.reserve(totalCount);
	unsigned int totalIndices = (m_vertexCountW - 1) * (m_vertexCountD * 2) + (m_vertexCountW - 2) + (m_vertexCountD - 2);
	indices.reserve(totalIndices);

	// Generate vertices
	for (int vx = 0; vx < m_vertexCountW; vx++) {
		for (int vz = 0; vz < m_vertexCountD; vz++) {
			MeshVertex mv;
			
			// We add or subtract half of the plane dimensions to center the mesh pivot on the center
			float posX = vx * stepX - m_width * 0.5f;
			float posZ = -vz * stepZ + m_depth * 0.5f; // vz is negative because the terrain expands towards -Z
			mv.Position = { posX, 0.0f, posZ };
			mv.Normal = { 0.0f, 1.0f, 0.0f };
			mv.Tangent = { 1.0f, 0.0f, 0.0f };
			mv.Bitangent = { 0.0f, 0.0f, -1.0f }; // expands towards -z
			float u = (float)vx / (m_vertexCountW - 1);
			float v = (float)vz / (m_vertexCountD - 1);
			mv.TexCoord = { u, v };

			vertices.push_back(mv);
		}
	}

	// Generate indices
	CalculateIndices(indices);

	JASS_ASSERT(indices.size(), "The index buffer is empty");

	return Mesh(PrepareVAO(vertices, indices), Jass::RenderMode::TriangleStrip);
}

Jass::Ref<Jass::VertexArray> Plane::PrepareVAO(std::vector<MeshVertex>& vertices, std::vector<unsigned int>& indices)
{
	auto vertexArray = Jass::VertexArray::Create();

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

	vertexArray->AddVertexBuffer(vbo);

	Jass::Ref<Jass::IndexBuffer> ibo = Jass::IndexBuffer::Create({ &indices[0], (unsigned int)indices.size(), Jass::DataUsage::StaticDraw });

	vertexArray->SetIndexBuffer(ibo);

	return vertexArray;
}

void Plane::CalculateIndices(std::vector<unsigned int>& indices)
{
	int minCol = 0;
	int maxCol = std::max(m_vertexCountW - 2, 0);

	int minRow = 0;
	int maxRow = std::max(m_vertexCountD - 1, 0);

	// The Plane is not visible
	if (minCol == maxCol && minRow == maxRow)
		return;

	for (int c = minCol; c <= maxCol; c++) {
		for (int r = minRow; r <= maxRow; r++) {

			// If it is not the first strip, generate a link with the previous strip (degenerate triangle)
			if (c > minCol && r == minRow)
				indices.push_back(c * m_vertexCountD + r);

			indices.push_back(c * m_vertexCountD + r);
			indices.push_back((c + 1) * m_vertexCountD + r);

			// Link with the next triangle strip (degenerate triangle)
			if (r == maxRow && c < maxCol)
				indices.push_back((c + 1) * m_vertexCountD + r);
		}
	}
}
