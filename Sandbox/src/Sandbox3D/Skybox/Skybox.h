#ifndef SKYBOX_H
#define SKYBOX_H

#include "Jass.h"

class Skybox {

public:
	Skybox();

	void SetTexture(const std::vector<std::string>& filenames);

	void Render(const Jass::Ref<Jass::Shader>& shader, const Jass::Camera& camera);

private:
	Jass::Ref<Jass::Texture3D> m_texture;
	Jass::Ref<Jass::VertexArray> m_vertexArray;

};

#endif // !SKYBOX_H
