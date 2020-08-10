#include "jasspch.h"

#include "JMath.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Jass {

	JMat4 Scale(const JMat4& matrix, const JVec3& vector)
	{
		return glm::scale(matrix, vector);
	}

	JMat4 Translate(const JMat4& matrix, const JVec3& vector)
	{
		return glm::translate(matrix, vector);
	}

	JMat4 Rotate(const JMat4& matrix, float angle, const JVec3& vector)
	{
		return glm::rotate(matrix, angle, vector);
	}

	JMat4 PerspectiveFOV(float fov, float width, float height, float zNear, float zFar)
	{
		return glm::perspectiveFov(fov, width, height, zNear, zFar);
	}

	JMat4 Orthographic(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f)
	{
		return glm::ortho(left, right, bottom, top, zNear, zFar);
	}

	float Radians(float degrees)
	{
		return glm::radians(degrees);
	}

	float* GetPtr(JMat3& matrix)
	{
		return glm::value_ptr(matrix);
	}

	float* GetPtr(JMat4& matrix)
	{
		return glm::value_ptr(matrix);
	}

	float* GetPtr(JVec4& vector)
	{
		return glm::value_ptr(vector);
	}

	const float* GetPtr(const JMat3& matrix)
	{
		return glm::value_ptr(matrix);
	}

	const float* GetPtr(const JMat4& matrix)
	{
		return glm::value_ptr(matrix);
	}

	const float* GetPtr(const JVec4& vector)
	{
		return glm::value_ptr(vector);
	}

}