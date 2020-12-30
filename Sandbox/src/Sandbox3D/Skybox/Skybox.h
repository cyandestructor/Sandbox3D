#ifndef SKYBOX_H
#define SKYBOX_H

#include "Jass.h"

class Skybox {

public:
	Skybox();

	void SetTexture(const std::vector<std::string>& filenames);

	void SetShader(const Jass::Ref<Jass::Shader>& shader) { m_shader = shader; }

	void SetCamera(const Jass::Camera& camera);

	void Render();

private:
	Jass::Ref<Jass::Shader> m_shader;
	Jass::Ref<Jass::Texture3D> m_texture;
	Jass::Ref<Jass::VertexArray> m_vertexArray;

};

#endif // !SKYBOX_H
