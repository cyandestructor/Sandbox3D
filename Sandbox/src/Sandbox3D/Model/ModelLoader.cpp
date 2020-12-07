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
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				MeshVertex mv;

				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				mv.Position.x = attrib.vertices[3 * idx.vertex_index + 0];
				mv.Position.y = attrib.vertices[3 * idx.vertex_index + 1];
				mv.Position.z = attrib.vertices[3 * idx.vertex_index + 2];
				mv.Normal.x = attrib.normals[3 * idx.normal_index + 0];
				mv.Normal.y = attrib.normals[3 * idx.normal_index + 1];
				mv.Normal.z = attrib.normals[3 * idx.normal_index + 2];
				mv.TexCoord.x = attrib.texcoords[2 * idx.texcoord_index + 0];
				mv.TexCoord.y = attrib.texcoords[2 * idx.texcoord_index + 1];

				vertices.push_back(mv);
				indices.push_back(index++);
			}

			index_offset += fv;
		}
	}
}

static void CalcNormal(float N[3], float v0[3], float v1[3], float v2[3]) {
	float v10[3];
	v10[0] = v1[0] - v0[0];
	v10[1] = v1[1] - v0[1];
	v10[2] = v1[2] - v0[2];

	float v20[3];
	v20[0] = v2[0] - v0[0];
	v20[1] = v2[1] - v0[1];
	v20[2] = v2[2] - v0[2];

	N[0] = v10[1] * v20[2] - v10[2] * v20[1];
	N[1] = v10[2] * v20[0] - v10[0] * v20[2];
	N[2] = v10[0] * v20[1] - v10[1] * v20[0];

	float len2 = N[0] * N[0] + N[1] * N[1] + N[2] * N[2];
	if (len2 > 0.0f) {
		float len = sqrtf(len2);

		N[0] /= len;
		N[1] /= len;
		N[2] /= len;
	}
}

void ModelLoader::ReadFile2(const std::string& filename, std::vector<MeshVertex>& vertices, std::vector<unsigned int>& indices)
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

	unsigned int index = 0;
	for (size_t s = 0; s < shapes.size(); s++) {
		std::vector<float> buffer;  // pos(3float), normal(3float), color(3float)

		for (size_t f = 0; f < shapes[s].mesh.indices.size() / 3; f++) {
			tinyobj::index_t idx0 = shapes[s].mesh.indices[3 * f + 0];
			tinyobj::index_t idx1 = shapes[s].mesh.indices[3 * f + 1];
			tinyobj::index_t idx2 = shapes[s].mesh.indices[3 * f + 2];

			float tc[3][2];
			if (attrib.texcoords.size() > 0) {
				if ((idx0.texcoord_index < 0) || (idx1.texcoord_index < 0) ||
					(idx2.texcoord_index < 0)) {
					// face does not contain valid uv index.
					tc[0][0] = 0.0f;
					tc[0][1] = 0.0f;
					tc[1][0] = 0.0f;
					tc[1][1] = 0.0f;
					tc[2][0] = 0.0f;
					tc[2][1] = 0.0f;
				}
				else {
					assert(attrib.texcoords.size() >
						size_t(2 * idx0.texcoord_index + 1));
					assert(attrib.texcoords.size() >
						size_t(2 * idx1.texcoord_index + 1));
					assert(attrib.texcoords.size() >
						size_t(2 * idx2.texcoord_index + 1));

					// Flip Y coord.
					tc[0][0] = attrib.texcoords[2 * idx0.texcoord_index];
					tc[0][1] = 1.0f - attrib.texcoords[2 * idx0.texcoord_index + 1];
					tc[1][0] = attrib.texcoords[2 * idx1.texcoord_index];
					tc[1][1] = 1.0f - attrib.texcoords[2 * idx1.texcoord_index + 1];
					tc[2][0] = attrib.texcoords[2 * idx2.texcoord_index];
					tc[2][1] = 1.0f - attrib.texcoords[2 * idx2.texcoord_index + 1];
				}
			}
			else {
				tc[0][0] = 0.0f;
				tc[0][1] = 0.0f;
				tc[1][0] = 0.0f;
				tc[1][1] = 0.0f;
				tc[2][0] = 0.0f;
				tc[2][1] = 0.0f;
			}

			float v[3][3];
			for (int k = 0; k < 3; k++) {
				int f0 = idx0.vertex_index;
				int f1 = idx1.vertex_index;
				int f2 = idx2.vertex_index;
				assert(f0 >= 0);
				assert(f1 >= 0);
				assert(f2 >= 0);

				v[0][k] = attrib.vertices[3 * f0 + k];
				v[1][k] = attrib.vertices[3 * f1 + k];
				v[2][k] = attrib.vertices[3 * f2 + k];
			}

			float n[3][3];
			{
				bool invalid_normal_index = false;
				if (attrib.normals.size() > 0) {
					int nf0 = idx0.normal_index;
					int nf1 = idx1.normal_index;
					int nf2 = idx2.normal_index;

					if ((nf0 < 0) || (nf1 < 0) || (nf2 < 0)) {
						// normal index is missing from this face.
						invalid_normal_index = true;
					}
					else {
						for (int k = 0; k < 3; k++) {
							assert(size_t(3 * nf0 + k) < attrib.normals.size());
							assert(size_t(3 * nf1 + k) < attrib.normals.size());
							assert(size_t(3 * nf2 + k) < attrib.normals.size());
							n[0][k] = attrib.normals[3 * nf0 + k];
							n[1][k] = attrib.normals[3 * nf1 + k];
							n[2][k] = attrib.normals[3 * nf2 + k];
						}
					}
				}
				else {
					invalid_normal_index = true;
				}

				if (invalid_normal_index) {
					// compute geometric normal
					CalcNormal(n[0], v[0], v[1], v[2]);
					n[1][0] = n[0][0];
					n[1][1] = n[0][1];
					n[1][2] = n[0][2];
					n[2][0] = n[0][0];
					n[2][1] = n[0][1];
					n[2][2] = n[0][2];
				}
			}

			for (int k = 0; k < 3; k++) {
				MeshVertex mv;
				mv.Position.x = v[k][0];
				mv.Position.y = v[k][1];
				mv.Position.y = v[k][2];
				mv.Normal.x = n[k][0];
				mv.Normal.x = n[k][1];
				mv.Normal.x = n[k][2];
				mv.TexCoord.x = tc[k][0];
				mv.TexCoord.x = tc[k][1];

				vertices.push_back(mv);
				indices.push_back(index++);
			}
		}
	}
}
