#include "jasspch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Jass {

	OrthographicCamera::OrthographicCamera(const OrthographicCameraSettings& settings)
	{
		m_settings = settings;

		m_projection = glm::ortho(
			settings.Left,
			settings.Right,
			settings.Bottom,
			settings.Top,
			-1.0f, 1.0f
		);

		CalculateMatrices();
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_settings.Position = position;
		CalculateMatrices();
	}

	void OrthographicCamera::SetRotation(const glm::vec3& rotation)
	{
		m_settings.Rotation = rotation;
		CalculateMatrices();
	}

	void OrthographicCamera::CalculateMatrices()
	{
		m_view = glm::translate(glm::mat4(1.0f), -m_settings.Position);
		m_view = glm::rotate(m_view, glm::radians(m_settings.Rotation.x), glm::vec3(-1.0f, 0.0f, 0.0f));
		m_view = glm::rotate(m_view, glm::radians(m_settings.Rotation.y), glm::vec3(0.0f, -1.0f, 0.0f));
		m_view = glm::rotate(m_view, glm::radians(m_settings.Rotation.z), glm::vec3(0.0f, 0.0f, -1.0f));

		m_viewProjection = m_projection * m_view;
	}

}