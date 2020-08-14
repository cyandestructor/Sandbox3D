#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_H_JASS
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_H_JASS

#include "OrthographicCamera.h"
#include "Jass/Core/Timestep.h"
#include "Jass/Events/ApplicationEvents.h"
#include "Jass/Events/MouseEvents.h"

namespace Jass {

	class JASS_API OrthographicCameraController {

	public:
		OrthographicCameraController(float aspectRatio, bool enableRotation = false);

		OrthographicCamera& GetCamera() { return m_camera; }
		const OrthographicCamera& GetCamera() const { return m_camera; }

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void SetCameraMoveSpeed(float speed) { m_cameraMoveSpeed = speed; }
		void SetCameraRotationSpeed(float rotationSpeed) { m_cameraRotationSpeed = rotationSpeed; }

	private:
		float m_aspectRatio;
		float m_zoom = 1.0f;

		OrthographicCamera m_camera;

		bool m_rotate;
		float m_cameraMoveSpeed = 3.0f;
		float m_cameraRotationSpeed = 180.0f;

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	};

}

#endif // !ORTHOGRAPHIC_CAMERA_CONTROLLER_H_JASS
