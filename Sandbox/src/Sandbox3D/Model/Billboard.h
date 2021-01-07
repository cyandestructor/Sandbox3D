#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "Jass.h"
#include "Material.h"

class Billboard {

public:
	Billboard();
	Billboard(const Jass::JVec3& position, const Jass::JVec3& scale);

	void SetPosition(const Jass::JVec3& position) { m_position = position; }
	const Jass::JVec3& GetPosition() const { return m_position; }
	
	void SetScale(const Jass::JVec3& scale) { m_scale = scale; }
	const Jass::JVec3& GetScale() const { return m_scale; }

	Material& GetMaterial() { return m_material; }

	void Render(Jass::Ref<Jass::Shader>& shader, const Light& light, const Jass::Camera& camera);

private:
	Jass::Ref<Jass::VertexArray> m_vertexArray;

	Jass::JVec3 m_position = Jass::JVec3(0.0f);
	Jass::JVec3 m_scale = Jass::JVec3(1.0f);

	Material m_material;
};

#endif // !BILLBOARD_H
