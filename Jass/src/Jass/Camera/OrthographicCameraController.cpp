#include "jasspch.h"
#include "OrthographicCameraController.h"

#include "Jass/Core/Input.h"
#include "Jass/Core/KeyCodes.h"
#include "Jass/Events/EventDispatcher.h"

namespace Jass {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool enableRotation) :
		m_rotate(enableRotation),
		m_aspectRatio(aspectRatio),
		m_camera({ -aspectRatio * m_zoom, aspectRatio * m_zoom, -m_zoom, m_zoom })
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		JASS_PROFILE_FUNCTION();

		auto cameraPosition = m_camera.GetPosition();
		auto cameraRotation = m_camera.GetRotation();

		if (Input::IsKeyPressed(JASS_KEY_UP))
			cameraPosition.y += m_cameraMoveSpeed * ts;
		else if (Input::IsKeyPressed(JASS_KEY_DOWN))
			cameraPosition.y -= m_cameraMoveSpeed * ts;

		if (Input::IsKeyPressed(JASS_KEY_RIGHT))
			cameraPosition.x += m_cameraMoveSpeed * ts;
		else if (Input::IsKeyPressed(JASS_KEY_LEFT))
			cameraPosition.x -= m_cameraMoveSpeed * ts;
		
		m_camera.SetPosition(cameraPosition);

		if (m_rotate) {
			if (Input::IsKeyPressed(JASS_KEY_A))
				cameraRotation.z += m_cameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(JASS_KEY_D))
				cameraRotation.z -= m_cameraRotationSpeed * ts;

			m_camera.SetRotation(cameraRotation);
		}
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResizeEvent));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_zoom -= e.GetYOffset() * 0.25f;
		m_zoom = std::max(m_zoom, 0.25f);
		m_camera.SetProjection(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom);
		
		return false;
	}

	bool OrthographicCameraController::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_camera.SetProjection(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom);
		
		return false;
	}

}
