#include "Terrain.h"

#include "../Primitives/Plane.h"
#include "../stb_image/stb_image.h"

// A little hacky hack ;) Of course is temporary

float baryCentric(const Jass::JVec3& p1, const Jass::JVec3& p2, const Jass::JVec3& p3, const Jass::JVec2& pos) {
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

Terrain::Terrain(const std::string& heightMap, unsigned int width, unsigned int height)
	: m_width((float)width), m_height((float)height)
{
	m_terrainMesh = Generate(heightMap, width, height);
}

Terrain::Terrain(unsigned int width, unsigned int height, unsigned int wDiv, unsigned int hDiv)
	: m_width((float)width), m_height((float)height)
{
	Plane terrainPlane(width, height, wDiv, hDiv);
	m_terrainMesh = terrainPlane.Generate();
}

float Terrain::GetTerrainHeight(float worldX, float worldZ) const
{
	float terrainX = worldX - m_position.x;
	float terrainZ = worldZ - m_position.z;

	// Note this only works on square terrains

	int inW = (int)m_terrainHeight.size() - 1;
	int inH = (int)m_terrainHeight[0].size() - 1;

	float gridSqW = m_width / (inW);
	float gridSqH = m_height / (inH);

	int gridX = (int)floor(terrainX / gridSqW);
	int gridZ = (int)floor(terrainZ / gridSqH);

	if (gridX >= inW || gridX < 0 || gridZ >= inH || gridZ < 0)
		return 0.0f;

	// Between 0 and 1
	float xCoord = fmod(terrainX, gridSqW) / gridSqW;
	float zCoord = fmod(terrainZ, gridSqH) / gridSqH;

	float result;
	if (xCoord <= (1 - zCoord))
	{
		result = baryCentric({ 0, m_terrainHeight[gridX][gridZ], 0 },
			{ 1, m_terrainHeight[gridX + 1][gridZ], 0 },
			{ 0, m_terrainHeight[gridX][gridZ + 1], 1 },
			{ xCoord, zCoord });
	}
	else
	{
		result = baryCentric({ 1, m_terrainHeight[gridX + 1][gridZ], 0 },
			{ 1, m_terrainHeight[gridX + 1][gridZ + 1], 1 },
			{ 0, m_terrainHeight[gridX][gridZ + 1], 1 },
			{ xCoord, zCoord });
	}

	return result;
}

void Terrain::SetBlendMap(const std::string& blendmap)
{
	TerrainTexture tt;
	tt.Texture = Jass::Texture2D::Create(blendmap);
	tt.Slot = 0;
	tt.UniformName = "u_blendMap";

	m_terrainTextures.push_back(tt);
}

void Terrain::AddTexture(const std::string& texture, const std::string& uniformName, unsigned int slot)
{
	TerrainTexture tt;
	tt.Texture = Jass::Texture2D::Create(texture);
	tt.UniformName = uniformName;
	tt.Slot = slot;
	m_terrainTextures.push_back(tt);
}

void Terrain::Render(Jass::Ref<Jass::Shader>& shader, const Light& light)
{
	shader->Bind();
	
	shader->SetFloat4("u_lightColor", light.GetColor());
	shader->SetFloat3("u_lightPosition", light.GetPosition());

	shader->SetFloat("u_ambientReduction", m_ambientReduction);
	shader->SetFloat("u_diffuseReduction", m_diffuseReduction);

	shader->SetFloat("u_repeatFactor", m_uvRepeat);
	
	for (const auto& texture : m_terrainTextures)
	{
		if (texture.Texture)
		{
			texture.Texture->Bind(texture.Slot);
			shader->SetInt(texture.UniformName, texture.Slot);
		}
	}

	Jass::Renderer::Submit(shader, m_terrainMesh.GetVertexArray());
}

Mesh Terrain::Generate(const std::string& heightmap, unsigned int width, unsigned int height)
{	
	std::vector<MeshVertex> vertices;
	std::vector<unsigned int> indices;
	
	int imgWidth, imgHeight, channels;
	stbi_uc* data = nullptr;
	{
		stbi_set_flip_vertically_on_load(1);
		data = stbi_load(heightmap.c_str(), &imgWidth, &imgHeight, &channels, 0);
	}
	if (!data) {
		JASS_LOG_WARN("The image {0} could not be loaded", heightmap);
	}

	ImageInfo imgInfo;
	imgInfo.Image = data;
	imgInfo.Channels = channels;
	imgInfo.Width = imgWidth;
	imgInfo.Height = imgHeight;

	unsigned int vertexCountW = imgWidth;
	unsigned int vertexCountH = imgHeight;

	// 2D Vector
	m_terrainHeight = std::vector<std::vector<float>>(vertexCountW, std::vector<float>(vertexCountH));

	unsigned int totalCount = vertexCountH * vertexCountW;
	vertices.reserve(totalCount);
	indices.reserve(6 * ((size_t)vertexCountW - 1) * ((size_t)vertexCountH - 1));

	// TODO: CHECK THIS ALGORITHM FOR NONE SQUARE PLANES

	for (unsigned int i = 0; i < vertexCountW; i++)
	{
		for (unsigned int j = 0; j < vertexCountH; j++)
		{
			MeshVertex mv;
			mv.Position.x = -(float)j / ((float)vertexCountW - 1) * (float)width;
			float vHeight = GetHeight(data, j, i, channels, imgWidth, imgHeight);
			m_terrainHeight[j][i] = vHeight;
			mv.Position.y = vHeight;
			mv.Position.z = -(float)i / ((float)vertexCountH - 1) * (float)height;
			mv.Normal = CalculateNormal(j, i, imgInfo);
			mv.TexCoord.x = (float)j / ((float)vertexCountW - 1);
			mv.TexCoord.y = (float)i / ((float)vertexCountH - 1);

			vertices.push_back(mv);
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

			indices.push_back(topLeft);
			indices.push_back(bottomLeft);
			indices.push_back(topRight);
			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
		}
	}

	if (data)
		stbi_image_free(data);

	return Mesh(vertices, indices);
}

float Terrain::GetHeight(unsigned char* image, unsigned int x, unsigned int y, unsigned int channels, unsigned int imgWidth, unsigned int imgHeight)
{
	const float MAX_PIXEL_COLOR = 255 * 255 * 255;

	if (!image)
		return 0.0f;

	if (x >= imgWidth || y >= imgHeight)
		return 0.0f;

	unsigned int bytePerPixel = channels;
	unsigned char* pixelOffset = image + (x + imgHeight * y) * bytePerPixel;

	float height = float(pixelOffset[0] * pixelOffset[1] * pixelOffset[2]);
	height += MAX_PIXEL_COLOR / 2;
	height /= MAX_PIXEL_COLOR / 2;

	return height * m_maxHeight;
}

Jass::JVec3 Terrain::CalculateNormal(unsigned int x, unsigned int y, ImageInfo& imgInfo)
{
	float heightL = GetHeight(imgInfo.Image, x - 1, y, imgInfo.Channels, imgInfo.Width, imgInfo.Height);
	float heightR = GetHeight(imgInfo.Image, x + 1, y, imgInfo.Channels, imgInfo.Width, imgInfo.Height);
	float heightD = GetHeight(imgInfo.Image, x, y - 1, imgInfo.Channels, imgInfo.Width, imgInfo.Height);
	float heightU = GetHeight(imgInfo.Image, x, y + 1, imgInfo.Channels, imgInfo.Width, imgInfo.Height);

	Jass::JVec3 normal = { heightL - heightR, 2.0f, heightD - heightU };

	return Jass::Normalize(normal);
}
