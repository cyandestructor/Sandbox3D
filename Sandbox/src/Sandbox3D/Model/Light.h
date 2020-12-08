#ifndef LIGHT_H
#define LIGHT_H

#include "Jass.h"

class Light {

public:
	Light() = default;
	Light(const Jass::JVec3& position, const Jass::JVec4& color) : m_position(position), m_color(color) {}

	void SetPosition(const Jass::JVec3& position) { m_position = position; }
	const Jass::JVec3& GetPosition() const { return m_position; }

	void SetColor(const Jass::JVec4& color) { m_color = color; }
	const Jass::JVec4& GetColor() const { return m_color; }

private:
	Jass::JVec3 m_position = Jass::JVec3(0.0f);
	Jass::JVec4 m_color = Jass::JVec4(1.0f);

};

#endif // !LIGHT_H
