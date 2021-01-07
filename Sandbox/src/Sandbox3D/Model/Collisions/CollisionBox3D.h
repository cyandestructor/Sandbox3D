#ifndef COLLISION_BOX_3D_H
#define COLLISION_BOX_3D_H

#include "Jass.h"

class CollisionBox3D {

public:
	CollisionBox3D(const Jass::JVec3& position, float width, float height, float depth);

	bool Collision(const Jass::JVec3& point) const;
	bool Collision(const CollisionBox3D& box) const;

	void SetPosition(const Jass::JVec3& position);
	const Jass::JVec3& GetPosition() const { return m_position; }

	void SetWidth(float width) { m_width = width; CalculateMinMax(); }
	float GetWidth() const { return m_width; }
	
	void SetHeight(float height) { m_height = height; CalculateMinMax(); }
	float GetHeight() const { return m_height; }

	void SetDepth(float depth) { m_depth = depth; CalculateMinMax(); }
	float GetDepth() const { return m_depth; }

	const Jass::JVec3& GetMin() const { return m_min; }
	const Jass::JVec3& GetMax() const { return m_max; }

private:
	float m_width, m_height, m_depth;
	Jass::JVec3 m_position = Jass::JVec3(0.0f);
	Jass::JVec3 m_min;
	Jass::JVec3 m_max;

	void CalculateMinMax();

};

#endif // !COLLISION_BOX_3D_H
