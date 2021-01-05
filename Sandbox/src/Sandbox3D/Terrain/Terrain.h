#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Model/Mesh.h"
#include "../Model/Light.h"

class Terrain {

public:
	Terrain(const std::string& heightMap, unsigned int width, unsigned int depth, float step);

	void SetMaxHeight(float height) { m_maxHeight = height; }

	void SetPosition(const Jass::JVec3& position);
	const Jass::JVec3& GetPosition() const { return m_position; }

	void SetAmbientReduction(float reductionFactor) { m_ambientReduction = reductionFactor; }
	void SetDiffuseReduction(float reductionFactor) { m_diffuseReduction = reductionFactor; }

	float GetTerrainHeight(float worldX, float worldZ) const;

	void SetBlendMap(const std::string& blendmap);

	void SetUVRepeat(float repeatFactor) { m_uvRepeat = repeatFactor; }
	void AddTexture(const std::string& texture, const std::string& uniformName, unsigned int slot);

	void Render(Jass::Ref<Jass::Shader>& shader, const Light& light, const Jass::JVec4& clipPlane = Jass::JVec4(0.0f));

private:
	Jass::Ref<Jass::VertexArray> m_vertexArray;
	
	float m_ambientReduction = 1.0f, m_diffuseReduction = 1.0f;
	
	int m_width, m_depth;
	float m_step;

	Jass::JVec3 m_position = Jass::JVec3(0.0f);

	Jass::JMat4 m_transformation = Jass::JMat4(1.0f);

	float m_uvRepeat = 1.0f;
	float m_maxHeight = 20.0f;

	std::vector<std::vector<float>> m_terrainHeight;

	struct TerrainTexture
	{
		Jass::Ref<Jass::Texture2D> Texture;
		unsigned int Slot;
		std::string UniformName;
	};

	std::vector<TerrainTexture> m_terrainTextures;

	Jass::Ref<Jass::VertexArray> Generate(const std::string& heightmap, unsigned int width, unsigned int depth, float step);
	void CalculateIndices(std::vector<unsigned int>& indices);
	Jass::Ref<Jass::VertexArray> PrepareVAO(std::vector<MeshVertex>& vertices, std::vector<unsigned int>& indices);
	
	struct ImageInfo {
		unsigned char* Image;
		unsigned int Channels;
		unsigned int Width;
		unsigned int Height;
	};

	float GetHeight(ImageInfo& imgInfo, int x, int z);
	float GetHeight(int x, int z) const;
	Jass::JVec3 CalculateNormal(unsigned int x, unsigned int y, ImageInfo& imgInfo);
	void CalculateTangentsBitangents(std::vector<MeshVertex>& vertices);

};

#endif // !TERRAIN_H
