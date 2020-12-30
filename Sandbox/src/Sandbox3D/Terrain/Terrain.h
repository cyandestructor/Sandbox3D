#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Model/Mesh.h"
#include "../Model/Light.h"

class Terrain {

public:
	Terrain(const std::string& heightMap, unsigned int width, unsigned int height);
	Terrain(unsigned int width, unsigned int height, unsigned int wDiv, unsigned int hDiv);

	void SetMaxHeight(float height) { m_maxHeight = height; }
	void SetPosition(const Jass::JVec3& position) { m_position = position; }

	void SetAmbientReduction(float reductionFactor) { m_ambientReduction = reductionFactor; }
	void SetDiffuseReduction(float reductionFactor) { m_diffuseReduction = reductionFactor; }

	float GetTerrainHeight(float worldX, float worldZ) const;

	void SetBlendMap(const std::string& blendmap);

	void SetUVRepeat(float repeatFactor) { m_uvRepeat = repeatFactor; }
	void AddTexture(const std::string& texture, const std::string& uniformName, unsigned int slot);

	void Render(Jass::Ref<Jass::Shader>& shader, const Light& light);

private:
	Mesh m_terrainMesh;

	float m_ambientReduction = 1.0f, m_diffuseReduction = 1.0f;
	float m_width, m_height;

	Jass::JVec3 m_position = Jass::JVec3(0.0f);

	float m_uvRepeat = 1.0f;
	float m_maxHeight = 20.0f;

	struct TerrainTexture
	{
		Jass::Ref<Jass::Texture2D> Texture;
		unsigned int Slot;
		std::string UniformName;
	};

	std::vector<std::vector<float>> m_terrainHeight;

	std::vector<TerrainTexture> m_terrainTextures;

	Mesh Generate(const std::string& heightmap, unsigned int width, unsigned int height);
	float GetHeight(unsigned char* image, unsigned int x, unsigned int y, unsigned int channels, unsigned int imgWidth, unsigned int imgHeight);

	struct ImageInfo {
		unsigned char* Image;
		unsigned int Channels;
		unsigned int Width;
		unsigned int Height;
	};

	Jass::JVec3 CalculateNormal(unsigned int x, unsigned int y, ImageInfo& imgInfo);

};

#endif // !TERRAIN_H
