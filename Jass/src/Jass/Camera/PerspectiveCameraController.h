#ifndef PERSPECTIVE_CAMERA_CONTROLLER_H
#define PERSPECTIVE_CAMERA_CONTROLLER_H

#include "PerspectiveCamera.h"
#include "Jass/Core/Timestep.h"
#include "Jass/Events/ApplicationEvents.h"
#include "Jass/Events/MouseEvents.h"

namespace Jass {

	class JASS_API PerspectiveCameraController {

	public:
		PerspectiveCameraController();

		PerspectiveCamera& GetCamera() { return m_camera; }
		const PerspectiveCamera& GetCamera() const { return m_camera; }

		void SetSpeed(float speed) { m_cameraSpeed = speed; }
		float GetSpeed() const { return m_cameraSpeed; }

		void SetPitch(float pitch) { m_pitch = pitch; }
		float GetPitch() const { return m_pitch; }

		void SetYaw(float yaw) { m_yaw = yaw; }
		float GetYaw() const { return m_yaw; }

		void SetSensitivity(float sensitivity) { m_sensitivity = sensitivity; }
		float GetSensitivity() const { return m_sensitivity; }

		void SetCollision(bool collision) { m_collision = collision; }

		void SetFlyMode(bool mode) { m_flyMode = mode; }

		void CalculateCamera();

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		void OnResize(unsigned int width, unsigned int height);

	private:
		PerspectiveCamera m_camera;
		JVec3 m_front = { 0.0f, 0.0f, -1.0f };

		bool m_collision = false;
		bool m_flyMode = true;

		float m_cameraSpeed = 20.0f;
		float m_sensitivity = 0.1f;

		bool m_firstMouse = true;
		float m_lastX = 0;
		float m_lastY = 0;

		float m_yaw = -90.0f;
		float m_pitch = 0;

		void ProcessInput(Timestep ts);
		void ProcessMouse(float x, float y);

		bool OnWindowResizeEvent(WindowResizeEvent& e);

	};

}

#endif // !PERSPECTIVE_CAMERA_CONTROLLER_H
