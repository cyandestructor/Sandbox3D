#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Material.h"

class Model {

public:
	Model();
	Model(const std::string& filename);

	void Load(const std::string& filename);

	const Jass::JMat4& GetTransformation() const { return m_transformation; }
	void SetTransformation(const Jass::JMat4& transformation) { m_transformation = transformation; }

	Material& GetMaterial() { return m_material; }

	void Render(Jass::Ref<Jass::Shader>& shader, const Light& light) const;

private:
	Mesh m_mesh;
	Material m_material;
	Jass::JMat4 m_transformation = Jass::JMat4(1.0f);

};

#endif // !MODEL_H
