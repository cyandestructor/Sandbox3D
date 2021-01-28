#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Jass.h"

class PlayerController {

public:
	Jass::PerspectiveCamera& GetCamera() { return m_camera; }
	const Jass::PerspectiveCamera& GetCamera() const { return m_camera; }

	void SetSpeed(float speed) { m_cameraSpeed = speed; }
	float GetSpeed() const { return m_cameraSpeed; }

	void SetPitch(float pitch) { m_pitch = pitch; }
	float GetPitch() const { return m_pitch; }

	void SetYaw(float yaw) { m_yaw = yaw; }
	float GetYaw() const { return m_yaw; }

	void SetJoystick(Jass::Joystick joystick) { m_joystick = joystick; }
	Jass::Joystick GetJoystick() const { return m_joystick; }

	void SetSensitivity(float sensitivity) { m_sensitivity = sensitivity; }
	float GetSensitivity() const { return m_sensitivity; }

	void SetGamepadSensitivity(float sensitivity) { m_gamepadSensitivity = sensitivity; }
	float GetGamepadSensitivy() const { return m_gamepadSensitivity; }

	void SetGamepadDeadZone(float deadZone) { m_gamepadDeadZone = deadZone; }
	float GetGamepadDeadZone() const { return m_gamepadDeadZone; }

	void SetCollision(bool collision) { m_collision = collision; }

	void CalculateCamera();

	void OnUpdate(Jass::Timestep ts);
	void OnEvent(Jass::Event& e);
	void OnResize(unsigned int width, unsigned int height);

private:
	Jass::PerspectiveCamera m_camera;
	Jass::JVec3 m_front = { 0.0f, 0.0f, -1.0f };

	Jass::Joystick m_joystick = Jass::Joystick::Slot1;

	bool m_collision = false;

	float m_cameraSpeed = 20.0f;
	float m_sensitivity = 0.1f;
	float m_gamepadDeadZone = 0.05f;
	float m_gamepadSensitivity = 0.5f;

	bool m_firstMouse = true;
	float m_lastX = 0;
	float m_lastY = 0;

	float m_yaw = -90.0f;
	float m_pitch = 0;

	void ProcessInput(Jass::Timestep ts);
	void ProcessMouse(float x, float y);
	void ProcessGamepad(Jass::Timestep ts);

	bool OnWindowResizeEvent(Jass::WindowResizeEvent& e);

};

#endif // !PLAYER_CONTROLLER_H
