#include "jasspch.h"
#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Jass {

	PerspectiveCamera::PerspectiveCamera(const PerspectiveCameraSettings& settings = PerspectiveCameraSettings())
	{
		m_settings = settings;

		m_projection = glm::perspectiveFov(
			m_settings.FOV,
			m_settings.ViewportWidth,
			m_settings.ViewportHeight,
			m_settings.Near,
			m_settings.Far
		);

		CalculateMatrices();
	}

	void PerspectiveCamera::SetPosition(const glm::vec3& position)
	{
		m_settings.Position = position;
		CalculateMatrices();
	}

	void PerspectiveCamera::SetRotation(const glm::vec3& rotation)
	{
		m_settings.Rotation = rotation;
		CalculateMatrices();
	}

	void PerspectiveCamera::CalculateMatrices()
	{
		m_view = glm::translate(glm::mat4(1.0f), -m_settings.Position);
		m_view = glm::rotate(m_view, glm::radians(m_settings.Rotation.x), glm::vec3(-1.0f, 0.0f, 0.0f));
		m_view = glm::rotate(m_view, glm::radians(m_settings.Rotation.y), glm::vec3(0.0f, -1.0f, 0.0f));
		m_view = glm::rotate(m_view, glm::radians(m_settings.Rotation.z), glm::vec3(0.0f, 0.0f, -1.0f));

		m_viewProjection = m_projection * m_view;
	}

}