#include "jasspch.h"
#include "OrthographicCamera.h"

namespace Jass {

	OrthographicCamera::OrthographicCamera(const OrthographicCameraSettings& settings)
	{
		m_settings = settings;

		m_projection = Orthographic(
			settings.Left,
			settings.Right,
			settings.Bottom,
			settings.Top,
			-1.0f, 1.0f
		);

		CalculateMatrices();
	}

	void OrthographicCamera::SetPosition(const JVec3& position)
	{
		m_settings.Position = position;
		CalculateMatrices();
	}

	void OrthographicCamera::SetRotation(const JVec3& rotation)
	{
		m_settings.Rotation = rotation;
		CalculateMatrices();
	}

	void OrthographicCamera::CalculateMatrices()
	{
		m_view = Translate(JMat4(1.0f), -m_settings.Position);
		m_view = Rotate(m_view, Radians(m_settings.Rotation.x), JVec3(-1.0f, 0.0f, 0.0f));
		m_view = Rotate(m_view, Radians(m_settings.Rotation.y), JVec3(0.0f, -1.0f, 0.0f));
		m_view = Rotate(m_view, Radians(m_settings.Rotation.z), JVec3(0.0f, 0.0f, -1.0f));

		m_viewProjection = m_projection * m_view;
	}

}