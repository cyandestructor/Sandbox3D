#ifndef PLANE_H
#define PLANE_H

#include "Primitive.h"

class Plane : public Primitive {

public:
	Plane() = default;
	Plane(unsigned int width, unsigned int height, unsigned int widthDiv, unsigned int heightDiv)
		: m_width(width), m_height(height), m_widthDiv(widthDiv), m_heightDiv(heightDiv) {}

	virtual Mesh Generate() override;

private:
	unsigned int m_widthDiv = 1, m_heightDiv = 1, m_width = 1, m_height = 1;

};

#endif // !PLANE_H
