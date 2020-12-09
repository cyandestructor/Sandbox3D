#include "Plane.h"

Mesh Plane::Generate()
{
    unsigned int vertexCountW = m_widthDiv + 1;
    unsigned int vertexCountH = m_heightDiv + 1;

    unsigned int totalCount = vertexCountH * vertexCountW;
    m_vertices.reserve(totalCount);
    m_indices.reserve(6 * ((size_t)vertexCountW - 1) * ((size_t)vertexCountH - 1));

    // TODO: CHECK THIS ALGORITHM FOR NONE SQUARE PLANES

    for (unsigned int i = 0; i < vertexCountW; i++)
    {
        for (unsigned int j = 0; j < vertexCountH; j++)
        {
            MeshVertex mv;
            mv.Position.x = -(float)i / ((float)vertexCountW - 1) * (float)m_width;
            mv.Position.y = 0.0f;
            mv.Position.z = -(float)j / ((float)vertexCountH - 1) * (float)m_height;
            mv.Normal = { 0.0f, 1.0f, 0.0f };
            mv.TexCoord.x = (float)i / ((float)vertexCountW - 1);
            mv.TexCoord.y = (float)j / ((float)vertexCountH - 1);

            m_vertices.push_back(mv);
        }
    }

    for (unsigned int i = 0; i < vertexCountW - 1; i++)
    {
        for (unsigned int j = 0; j < vertexCountH - 1; j++)
        {
            unsigned int topLeft = (i * vertexCountW) + j;
            unsigned int topRight = topLeft + 1;
            unsigned int bottomLeft = ((i + 1) * vertexCountW) + j;
            unsigned int bottomRight = bottomLeft + 1;

            m_indices.push_back(topLeft);
            m_indices.push_back(bottomLeft);
            m_indices.push_back(topRight);
            m_indices.push_back(topRight);
            m_indices.push_back(bottomLeft);
            m_indices.push_back(bottomRight);

        }
    }

    return Mesh(m_vertices, m_indices);
}
