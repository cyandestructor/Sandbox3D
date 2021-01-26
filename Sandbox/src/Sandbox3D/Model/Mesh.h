#ifndef MESH_H
#define MESH_H

#include "Jass.h"

struct MeshVertex {
	Jass::JVec3 Position;
	Jass::JVec3 Normal;
	Jass::JVec2 TexCoord;
	Jass::JVec3 Tangent;
	Jass::JVec3 Bitangent;
};

class Mesh {

public:
	Mesh() = default;
	Mesh(std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices);
	Mesh(const Jass::Ref<Jass::VertexArray>& vertexArray, Jass::RenderMode renderMode = Jass::RenderMode::Triangle)
		:m_renderMode(renderMode)
	{
		m_vertexArray = vertexArray;
	}

	void SetRenderMode(Jass::RenderMode renderMode) { m_renderMode = renderMode; }
	Jass::RenderMode GetRenderMode() const { return m_renderMode; }

	inline const Jass::Ref<Jass::VertexArray>& GetVertexArray() const { return m_vertexArray; }

private:
	Jass::Ref<Jass::VertexArray> m_vertexArray;
	Jass::RenderMode m_renderMode = Jass::RenderMode::Triangle;

	void CalculateTangentsBitangents(std::vector<MeshVertex>& vertices);

};

#endif // !MESH_H

