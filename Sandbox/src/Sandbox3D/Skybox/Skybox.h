#ifndef SKYBOX_H
#define SKYBOX_H

#include "Jass.h"

class Skybox {

public:
	Skybox();

	void SetTexture(const std::vector<std::string>& filenames);

	void AddTexture(const std::vector<std::string>& filenames, const std::string& uniformName, unsigned int slot);

	void BlendTextures(unsigned int first, unsigned int second, float blendLevel) {
		m_firstTexture = first;
		m_secondTexture = second;
		m_blendLevel = blendLevel;
	}

	void SetRotation(float rotation) { m_rotation = rotation; }

	void Render(const Jass::Ref<Jass::Shader>& shader, const Jass::Camera& camera);

private:
	Jass::Ref<Jass::Texture3D> m_texture;
	Jass::Ref<Jass::VertexArray> m_vertexArray;

	struct TextureInfo {
		Jass::Ref<Jass::Texture3D> Texture;
		std::string Name;
		unsigned int Slot;
	};

	unsigned int m_firstTexture = 0;
	unsigned int m_secondTexture = 0;
	float m_blendLevel = 0.0f;

	std::vector<TextureInfo> m_textures;

	float m_rotation;

};

#endif // !SKYBOX_H
