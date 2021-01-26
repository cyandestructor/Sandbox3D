#ifndef PLANE_H
#define PLANE_H

#include "Primitive.h"

class Plane : public Primitive {

public:
	Plane() = default;
	Plane(float width, float depth, unsigned int widthDiv, unsigned int depthDiv)
		: m_width(width), m_depth(depth), m_widthDiv(widthDiv), m_depthDiv(depthDiv),
		m_vertexCountW(widthDiv + 1), m_vertexCountD(depthDiv + 1) {}

	void SetWidth(float width) { m_width = width; }
	float GetWidth() const { return m_width; }

	void SetDepth(float depth) { m_depth = depth; }
	float GetDepth() const { return m_depth; }

	void SetWidthDivisions(unsigned int widthDiv) { m_widthDiv = widthDiv; }
	unsigned int GetWidthDivisions() const { return m_widthDiv; }

	void SetDepthDivisions(unsigned int depthDiv) { m_depthDiv = depthDiv; }
	unsigned int GetDepthDivisions() const { return m_depthDiv; }

	virtual Mesh Generate() override;

private:
	int m_widthDiv = 1, m_depthDiv = 1, m_vertexCountW, m_vertexCountD;
	float m_width = 1.0f, m_depth = 1.0f;

	Jass::Ref<Jass::VertexArray> PrepareVAO(std::vector<MeshVertex>& vertices, std::vector<unsigned int>& indices);
	void CalculateIndices(std::vector<unsigned int>& indices);

};

#endif // !PLANE_H
