#include "jasspch.h"
#include "PerspectiveCamera.h"

namespace Jass {

	PerspectiveCamera::PerspectiveCamera(const PerspectiveCameraSettings& settings)
	{
		m_settings = settings;

		m_projection = PerspectiveFOV(
			m_settings.FOV,
			m_settings.ViewportWidth,
			m_settings.ViewportHeight,
			m_settings.Near,
			m_settings.Far
		);

		CalculateMatrices();
	}

	void PerspectiveCamera::SetPosition(const JVec3& position)
	{
		m_settings.Position = position;
		CalculateMatrices();
	}

	void PerspectiveCamera::SetRotation(const JVec3& rotation)
	{
		m_settings.Rotation = rotation;
		CalculateMatrices();
	}

	void PerspectiveCamera::CalculateMatrices()
	{
		m_view = Translate(JMat4(1.0f), -m_settings.Position);
		m_view = Rotate(m_view, Radians(m_settings.Rotation.x), JVec3(-1.0f, 0.0f, 0.0f));
		m_view = Rotate(m_view, Radians(m_settings.Rotation.y), JVec3(0.0f, -1.0f, 0.0f));
		m_view = Rotate(m_view, Radians(m_settings.Rotation.z), JVec3(0.0f, 0.0f, -1.0f));

		m_viewProjection = m_projection * m_view;
	}

}