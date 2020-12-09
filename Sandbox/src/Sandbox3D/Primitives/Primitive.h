#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../Model/Mesh.h"

class Primitive {

public:
	virtual Mesh Generate() { return Mesh(m_vertices, m_indices); }

protected:
	std::vector<MeshVertex> m_vertices;
	std::vector<unsigned int> m_indices;

};

#endif // !PRIMITIVE_H
