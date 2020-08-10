#ifndef JMATH_H
#define JMATH_H

// JMath is a wrapper for the math library used in the Engine
// Objectives:
// 1. Consistency with the types in the whole code
// 2. Be able to replace the math library easily

#include <glm/glm.hpp>

namespace Jass {

	typedef glm::vec1 JVec1;
	typedef glm::vec2 JVec2;
	typedef glm::vec3 JVec3;
	typedef glm::vec4 JVec4;

	typedef glm::mat3 JMat3;
	typedef glm::mat4 JMat4;

	JMat4 Scale(const JMat4& matrix, const JVec3& vector);
	JMat4 Translate(const JMat4& matrix, const JVec3& vector);
	JMat4 Rotate(const JMat4& matrix, float angle, const JVec3& vector);
	JMat4 PerspectiveFOV(float fov, float width, float height, float zNear, float zFar);
	JMat4 Orthographic(float left, float right, float bottom, float top, float zNear, float zFar);
	float Radians(float degrees);
	float* GetPtr(JMat3& matrix);
	float* GetPtr(JMat4& matrix);
	float* GetPtr(JVec4& vector);
	const float* GetPtr(const JMat3& matrix);
	const float* GetPtr(const JMat4& matrix);
	const float* GetPtr(const JVec4& vector);

}

#endif // !JMATH_H
