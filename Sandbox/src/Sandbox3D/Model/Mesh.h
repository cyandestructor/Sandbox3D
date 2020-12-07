#ifndef MESH_H
#define MESH_H

#include "Jass.h"

struct MeshVertex {
	Jass::JVec3 Position;
	Jass::JVec3 Normal;
	Jass::JVec2 TexCoord;
};

class Mesh {

public:
	Mesh() = default;
	Mesh(const std::vector<MeshVertex>& vertices, const std::vector<unsigned int>& indices);

	inline const Jass::Ref<Jass::VertexArray>& GetVertexArray() const { return m_vertexArray; }

private:
	Jass::Ref<Jass::VertexArray> m_vertexArray;

};

#endif // !MESH_H

