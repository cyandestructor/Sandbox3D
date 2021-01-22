#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"

#include "ModelLoader.h"

Mesh ModelLoader::LoadFromFile(const std::string& filename)
{
	std::vector<MeshVertex> vertices;
	std::vector<unsigned int> indices;

	ReadFile(filename, vertices, indices);

	return { vertices, indices };

}

static Jass::JVec2 GetTexCoords(const tinyobj::attrib_t& attrib, tinyobj::index_t idx)
{
	Jass::JVec2 texCoords = Jass::JVec2(0.0f);

	// No texture coordinates or invalid texcoord index
	if (attrib.texcoords.empty() || idx.texcoord_index < 0)
		return texCoords;

	texCoords.x = attrib.texcoords[2 * (size_t)idx.texcoord_index + 0];
	texCoords.y = attrib.texcoords[2 * (size_t)idx.texcoord_index + 1];

	return texCoords;
}

static Jass::JVec3 CalculateNormal(const Jass::JVec3& v0, const Jass::JVec3&  v1, const Jass::JVec3& v2)
{
	Jass::JVec3 v01 = v1 - v0;
	Jass::JVec3 v02 = v2 - v0;

	float
		x = v01.y * v02.z - v01.z * v02.y,
		y = v01.z * v02.x - v01.x * v02.z,
		z = v01.x * v02.y - v01.y * v02.x;

	return Jass::Normalize({ x, y, z });
}

static void GetFaceNormals(std::vector<MeshVertex>& vertices,
	const tinyobj::attrib_t& attrib,
	const std::vector<tinyobj::index_t>& indices,
	size_t indexOffset)
{
	JASS_ASSERT(vertices.size() == 3, "Only triangle faces are supported");

	bool invalidFaceNormals = false;

	// No normals or invalid normal index
	if (attrib.normals.empty())
	{
		invalidFaceNormals = true;
	}
	else
	{
		int nf0 = indices[indexOffset + 0].normal_index;
		int nf1 = indices[indexOffset + 1].normal_index;
		int nf2 = indices[indexOffset + 2].normal_index;

		if ((nf0 < 0 || nf1 < 0 || nf2 < 0))
			invalidFaceNormals = true;
	}

	if (!invalidFaceNormals)
	{
		for (int i = 0; i < 3; i++)
		{
			vertices[i].Normal.x = attrib.normals[3 * (size_t)indices[indexOffset + i].normal_index + 0];
			vertices[i].Normal.y = attrib.normals[3 * (size_t)indices[indexOffset + i].normal_index + 1];
			vertices[i].Normal.z = attrib.normals[3 * (size_t)indices[indexOffset + i].normal_index + 2];
		}
	}
	else
	{
		const auto& v0 = vertices[0].Position;
		const auto& v1 = vertices[1].Position;
		const auto& v2 = vertices[2].Position;

		auto faceNormal = CalculateNormal(v0, v1, v2);
		for (auto& vertex : vertices)
		{
			vertex.Normal = faceNormal;
		}
	}

}

void ModelLoader::ReadFile(const std::string& filename, std::vector<MeshVertex>& vertices, std::vector<unsigned int>& indices)
{
	tinyobj::ObjReader objReader;

	if (!objReader.ParseFromFile(filename)) {
		if (!objReader.Error().empty()) {
			JASS_LOG_ERR("TinyObjLoader: {0}", objReader.Error());
		}
		JASS_ASSERT(false, "Could not read the obj file");
	}

	if (!objReader.Warning().empty()) {
		JASS_LOG_WARN("TinyObjLoader: {0}", objReader.Warning());
	}

	auto& attrib = objReader.GetAttrib();
	auto& shapes = objReader.GetShapes();

	// Loop over shapes
	unsigned int index = 0;
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t indexOffset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			std::vector<MeshVertex> buffer(fv);

			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				MeshVertex& mv = buffer[v];

				tinyobj::index_t idx = shapes[s].mesh.indices[indexOffset + v];
				mv.Position.x = attrib.vertices[3 * (size_t)idx.vertex_index + 0];
				mv.Position.y = attrib.vertices[3 * (size_t)idx.vertex_index + 1];
				mv.Position.z = attrib.vertices[3 * (size_t)idx.vertex_index + 2];
				//mv.Normal.x = attrib.normals[3 * (size_t)idx.normal_index + 0];
				//mv.Normal.y = attrib.normals[3 * (size_t)idx.normal_index + 1];
				//mv.Normal.z = attrib.normals[3 * (size_t)idx.normal_index + 2];
				mv.TexCoord = GetTexCoords(attrib, idx);

				//vertices.push_back(mv);
				//indices.push_back(index++);
			}

			GetFaceNormals(buffer, attrib, shapes[s].mesh.indices, indexOffset);

			for (size_t v = 0; v < fv; v++) {
				vertices.push_back(buffer[v]);
				indices.push_back(index++);
			}

			indexOffset += fv;
		}
	}
}