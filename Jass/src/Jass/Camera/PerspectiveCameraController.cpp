#include "jasspch.h"
#include "PerspectiveCameraController.h"

#include "Jass/Core/Input.h"
#include "Jass/Core/KeyCodes.h"
#include "Jass/Events/EventDispatcher.h"

namespace Jass {

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		ProcessInput(ts);
		m_camera.LookAtTarget(m_camera.GetPosition() + m_front);
	}

	void PerspectiveCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnMouseMovedEvent));
	}

	void PerspectiveCameraController::OnResize(unsigned int width, unsigned int height)
	{
	}

	void PerspectiveCameraController::ProcessInput(Timestep ts)
	{
		float speed = m_cameraSpeed * ts;

		auto cameraPosition = m_camera.GetPosition();
		auto rightVector = Normalize(Cross(m_front, m_camera.GetUpVector()));

		if (Input::IsKeyPressed(JASS_KEY_W))
			cameraPosition += m_front * speed;
		if (Input::IsKeyPressed(JASS_KEY_S))
			cameraPosition -= m_front * speed;
		if (Input::IsKeyPressed(JASS_KEY_A))
			cameraPosition -= rightVector * speed;
		if (Input::IsKeyPressed(JASS_KEY_D))
			cameraPosition += rightVector * speed;

		m_camera.SetPosition(cameraPosition);
	}

	void PerspectiveCameraController::ProcessMouse(float x, float y)
	{
		if (m_firstMouse) {
			m_lastX = x;
			m_lastY = y;
			m_firstMouse = false;
		}
		
		float offsetX = x - m_lastX;
		float offsetY = m_lastY - y;

		m_lastX = x;
		m_lastY = y;

		offsetX *= m_sensitivity;
		offsetY *= m_sensitivity;

		m_yaw += offsetX;
		m_pitch += offsetY;

		m_pitch = m_pitch > 89.0f ? 89.0f : m_pitch;
		m_pitch = m_pitch < -89.0f ? -89.0f : m_pitch;

		JVec3 direction;
		direction.x = cos(Radians(m_yaw)) * cos(Radians(m_pitch));
		direction.y = sin(Radians(m_pitch));
		direction.z = sin(Radians(m_yaw)) * cos(Radians(m_pitch));

		m_front = Normalize(direction);
	}

	bool PerspectiveCameraController::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ProcessMouse(e.GetX(), e.GetY());

		return false;
	}

}
