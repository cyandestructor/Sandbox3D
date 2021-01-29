#include "PlayerController.h"

void PlayerController::CalculateCamera()
{
	m_camera.LookAtTarget(m_camera.GetPosition() + m_front);
}

void PlayerController::OnUpdate(Jass::Timestep ts)
{
	if (Jass::Input::IsGamepadConnected(m_joystick))
	{
		ProcessGamepad(ts);
	}
	else if (Jass::Input::IsJoystickConnected(m_joystick))
	{
		ProcessJoystick(ts);
	}
	else
	{
		auto [x, y] = Jass::Input::GetMousePos();
		ProcessMouse(x, y);
		ProcessInput(ts);
	}

	CalculateCamera();
}

void PlayerController::OnEvent(Jass::Event& e)
{
	Jass::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Jass::WindowResizeEvent>(BIND_EVENT_FN(PlayerController::OnWindowResizeEvent));
}

void PlayerController::OnResize(unsigned int width, unsigned int height)
{
	const auto& cameraSettings = m_camera.GetSettings();
	m_camera.SetProjection(cameraSettings.FOV, (float)width, (float)height, cameraSettings.Near, cameraSettings.Far);
}

void PlayerController::ProcessInput(Jass::Timestep ts)
{
	float speed = m_cameraSpeed * ts;

	auto cameraPosition = m_camera.GetPosition();
	auto rightVector = Jass::Normalize(Jass::Cross(m_front, m_camera.GetUpVector()));

	if (m_collision) {
		if (Jass::Input::IsKeyPressed(JASS_KEY_W))
			cameraPosition += m_front * -speed;
		if (Jass::Input::IsKeyPressed(JASS_KEY_S))
			cameraPosition -= m_front * -speed;
		if (Jass::Input::IsKeyPressed(JASS_KEY_A))
			cameraPosition -= rightVector * -speed;
		if (Jass::Input::IsKeyPressed(JASS_KEY_D))
			cameraPosition += rightVector * -speed;
	}
	else {
		if (Jass::Input::IsKeyPressed(JASS_KEY_W))
			cameraPosition += m_front * speed;
		if (Jass::Input::IsKeyPressed(JASS_KEY_S))
			cameraPosition -= m_front * speed;
		if (Jass::Input::IsKeyPressed(JASS_KEY_A))
			cameraPosition -= rightVector * speed;
		if (Jass::Input::IsKeyPressed(JASS_KEY_D))
			cameraPosition += rightVector * speed;
	}

	m_camera.SetPosition(cameraPosition);
}

void PlayerController::ProcessMouse(float x, float y)
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

	Jass::JVec3 direction;
	direction.x = cos(Jass::Radians(m_yaw)) * cos(Jass::Radians(m_pitch));
	direction.y = sin(Jass::Radians(m_pitch));
	direction.z = sin(Jass::Radians(m_yaw)) * cos(Jass::Radians(m_pitch));

	m_front = Jass::Normalize(direction);
}

void PlayerController::ProcessGamepad(Jass::Timestep ts)
{
	float sensitivity = m_gamepadSensitivity;

	// Camera rotation

	float valueX = Jass::Input::GetGamepadAxis(m_joystick, Jass::GamepadAxis::RightX) * sensitivity;
	float valueY = -Jass::Input::GetGamepadAxis(m_joystick, Jass::GamepadAxis::RightY) * sensitivity;

	valueX = std::abs(valueX) > m_gamepadDeadZone ? valueX : 0.0f;
	valueY = std::abs(valueY) > m_gamepadDeadZone ? valueY : 0.0f;

	m_yaw += valueX;
	m_pitch += valueY;

	m_pitch = m_pitch > 89.0f ? 89.0f : m_pitch;
	m_pitch = m_pitch < -89.0f ? -89.0f : m_pitch;

	Jass::JVec3 direction;
	direction.x = cos(Jass::Radians(m_yaw)) * cos(Jass::Radians(m_pitch));
	direction.y = sin(Jass::Radians(m_pitch));
	direction.z = sin(Jass::Radians(m_yaw)) * cos(Jass::Radians(m_pitch));

	m_front = Jass::Normalize(direction);

	// Camera motion

	float speed = m_cameraSpeed * ts;

	auto cameraPosition = m_camera.GetPosition();
	auto rightVector = Jass::Normalize(Jass::Cross(m_front, m_camera.GetUpVector()));

	float frontMotion = -Jass::Input::GetGamepadAxis(m_joystick, Jass::GamepadAxis::LeftY) * sensitivity;
	float rightMotion = Jass::Input::GetGamepadAxis(m_joystick, Jass::GamepadAxis::LeftX) * sensitivity;

	frontMotion = std::abs(frontMotion) > m_gamepadDeadZone ? frontMotion : 0.0f;
	rightMotion = std::abs(rightMotion) > m_gamepadDeadZone ? rightMotion : 0.0f;

	cameraPosition += m_front * frontMotion * speed;
	cameraPosition += rightVector * rightMotion * speed;

	m_camera.SetPosition(cameraPosition);
}

void PlayerController::ProcessJoystick(Jass::Timestep ts)
{
	/* This is 100% mapped to my own gamepad (A gamecube controller),
	so it may not work for yours (it can even crash)*/
	const int ButtonA = 1;
	const int ButtonB = 2;
	const int ButtonX = 0;
	const int ButtonY = 3;
	const int buttonZ = 7;

	const int DpadUp = 12;
	const int DpadRight = 13;
	const int DpadDown = 14;
	const int DpadLeft = 15;

	const int LeftBumper = 4;
	const int RightBumper = 5;

	const int Start = 9;

	const int LeftAxisX = 0;
	const int LeftAxisY = 1;

	const int RightAxisX = 5;
	const int RightAxisY = 2;

	const int LeftTrigger = 3;

	auto buttons = Jass::Input::GetJoystickButtons(m_joystick);
	auto axes = Jass::Input::GetJoystickAxes(m_joystick);

	float sensitivity = m_gamepadSensitivity;

	float
		rightAxisX = 0.0f,
		rightAxisY = 0.0f,
		leftAxisX = 0.0f,
		leftAxisY = 0.0f;

	try
	{
		rightAxisX = axes[RightAxisX];
		rightAxisY = axes[RightAxisY];
		leftAxisX = axes[LeftAxisX];
		leftAxisY = axes[LeftAxisY];
	}
	catch (const std::exception& e)
	{
		JASS_LOG_ERR("Joystick axis could not be found and caused an exception");
		JASS_LOG_ERR("{0}", e.what());
	}

	// Camera rotation

	float valueX = -rightAxisX * sensitivity; // On my joystick, this axis seems to be inverted
	float valueY = rightAxisY * sensitivity;

	valueX = std::abs(valueX) > m_gamepadDeadZone ? valueX : 0.0f;
	valueY = std::abs(valueY) > m_gamepadDeadZone ? valueY : 0.0f;

	m_yaw += valueX;
	m_pitch += valueY;

	m_pitch = m_pitch > 89.0f ? 89.0f : m_pitch;
	m_pitch = m_pitch < -89.0f ? -89.0f : m_pitch;

	Jass::JVec3 direction;
	direction.x = cos(Jass::Radians(m_yaw)) * cos(Jass::Radians(m_pitch));
	direction.y = sin(Jass::Radians(m_pitch));
	direction.z = sin(Jass::Radians(m_yaw)) * cos(Jass::Radians(m_pitch));

	m_front = Jass::Normalize(direction);

	// Camera motion

	float speed = m_cameraSpeed * ts;

	auto cameraPosition = m_camera.GetPosition();
	auto rightVector = Jass::Normalize(Jass::Cross(m_front, m_camera.GetUpVector()));

	float frontMotion = -axes[LeftAxisY] * sensitivity; // On my joystick, this axis seems to be inverted
	float rightMotion = axes[LeftAxisX] * sensitivity;

	frontMotion = std::abs(frontMotion) > m_gamepadDeadZone ? frontMotion : 0.0f;
	rightMotion = std::abs(rightMotion) > m_gamepadDeadZone ? rightMotion : 0.0f;

	cameraPosition += m_front * frontMotion * speed;
	cameraPosition += rightVector * rightMotion * speed;

	m_camera.SetPosition(cameraPosition);
}

bool PlayerController::OnWindowResizeEvent(Jass::WindowResizeEvent& e)
{
	OnResize(e.GetWidth(), e.GetHeight());

	return false;
}
