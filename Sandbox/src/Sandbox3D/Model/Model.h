#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

class Model {

public:
	Model();
	Model(const std::string& filename);

	const Jass::JMat4& GetTransformation() const { return m_transformation; }
	void SetTransformation(const Jass::JMat4& transformation) { m_transformation = transformation; }
	void Load(const std::string& filename);

	void Render() const;

private:
	Mesh m_mesh;
	Jass::Ref<Jass::Shader> m_shader;
	Jass::JMat4 m_transformation = Jass::JMat4(1.0f);

};

#endif // !MODEL_H
