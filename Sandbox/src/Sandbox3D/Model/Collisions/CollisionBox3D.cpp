#include "CollisionBox3D.h"

CollisionBox3D::CollisionBox3D(const Jass::JVec3& position, float width, float height, float depth)
    :m_width(width), m_height(height), m_depth(depth)
{
    SetPosition(position);
}

bool CollisionBox3D::Collision(const Jass::JVec3& point) const
{
    return (point.x >= m_min.x && point.x <= m_max.x) &&
        (point.y >= m_min.y && point.y <= m_max.y) &&
        (point.z >= m_min.z && point.z <= m_max.z);
}

bool CollisionBox3D::Collision(const CollisionBox3D& box) const
{
    return (m_min.x <= box.m_max.x && m_max.x >= box.m_min.x) &&
        (m_min.y <= box.m_max.y && m_max.y >= box.m_min.y) &&
        (m_min.z <= box.m_max.z && m_max.z >= box.m_min.z);
}

void CollisionBox3D::SetPosition(const Jass::JVec3& position)
{
    if (position == m_position)
        return;

    m_position = position;
    CalculateMinMax();
}

void CollisionBox3D::CalculateMinMax()
{
    float minX = m_position.x - m_width * 0.5f;
    float maxX = m_position.x + m_width * 0.5f;

    float minY = m_position.y - m_height * 0.5f;
    float maxY = m_position.y + m_height * 0.5f;

    float minZ = m_position.z - m_depth * 0.5f;
    float maxZ = m_position.z + m_depth * 0.5f;

    m_min = { minX, minY, minZ };
    m_max = { maxX, maxY, maxZ };
}
