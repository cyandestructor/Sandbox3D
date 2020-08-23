#include "jasspch.h"
#include "OrthographicCamera.h"

namespace Jass {

	OrthographicCamera::OrthographicCamera(const OrthographicCameraSettings& settings)
	{
		JASS_PROFILE_FUNCTION();

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
		JASS_PROFILE_FUNCTION();

		m_settings.Position = position;
		CalculateMatrices();
	}

	void OrthographicCamera::SetRotation(const JVec3& rotation)
	{
		JASS_PROFILE_FUNCTION();

		m_settings.Rotation = rotation;
		CalculateMatrices();
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		JASS_PROFILE_FUNCTION();

		m_settings.Left = left;
		m_settings.Right = right;
		m_settings.Bottom = bottom;
		m_settings.Top = top;

		m_projection = Orthographic(
			m_settings.Left,
			m_settings.Right,
			m_settings.Bottom,
			m_settings.Top,
			-1.0f, 1.0f
		);

		m_viewProjection = m_projection * m_view;
	}

	void OrthographicCamera::CalculateMatrices()
	{
		JASS_PROFILE_FUNCTION();

		m_view = Translate(JMat4(1.0f), -m_settings.Position);
		m_view = Rotate(m_view, Radians(m_settings.Rotation.x), JVec3(-1.0f, 0.0f, 0.0f));
		m_view = Rotate(m_view, Radians(m_settings.Rotation.y), JVec3(0.0f, -1.0f, 0.0f));
		m_view = Rotate(m_view, Radians(m_settings.Rotation.z), JVec3(0.0f, 0.0f, -1.0f));

		m_viewProjection = m_projection * m_view;
	}

}