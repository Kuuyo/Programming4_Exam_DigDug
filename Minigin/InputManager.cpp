#include "MiniginPCH.h"
#include "InputManager.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include "glm/gtx/norm.hpp"
#pragma warning(pop)

// References:
// https://bell0bytes.eu/xinput-and-gamepads/
// https://docs.microsoft.com/en-us/windows/desktop/xinput/getting-started-with-xinput
// https://wiki.libsdl.org/

// TODO: Make InputManager a subject (instead of holding arrays of states ?)

void dae::InputManager::Initialize()
{
	m_PreviousKeyboardState = new UINT8[SDL_NUM_SCANCODES];
	m_CurrentKeyboardState = SDL_GetKeyboardState(NULL);
}

bool dae::InputManager::ProcessInput()
{
	// XInput
	m_PreviousState = m_CurrentState;

	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	if (!XInputGetState(0, &m_CurrentState) == ERROR_SUCCESS && !m_bControllerIsDisconnected)
	{
		LogWarningC("No controller found.");
		m_bControllerIsDisconnected = true;
	}

	// Keyboard
	memcpy(m_PreviousKeyboardState, m_CurrentKeyboardState, SDL_NUM_SCANCODES);
	m_PreviousKeyMods = m_CurrentKeyMods;

	SDL_Event e;
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT)
			return false;

	m_CurrentKeyMods = SDL_GetModState();

	return true;
}

#pragma region XInput

const bool dae::InputManager::IsPressed(const WORD button) const
{
	return (m_CurrentState.Gamepad.wButtons & button) != 0;
}

const bool dae::InputManager::WasPressed(const WORD button) const
{
	return (m_PreviousState.Gamepad.wButtons & button) != 0;
}

const dae::KeyState dae::InputManager::GetButtonState(const WORD button) const
{
	if (WasPressed(button))
		if (IsPressed(button))
			return KeyState::Held;
		else
			return KeyState::Released;
	else
		if (IsPressed(button))
			return KeyState::Triggered;
		else
			return KeyState::Default;
}

const float dae::InputManager::GetLeftTrigger() const
{
	return (float)m_CurrentState.Gamepad.bLeftTrigger / 255.0f;
}

const float dae::InputManager::GetRightTrigger() const
{
	return (float)m_CurrentState.Gamepad.bRightTrigger / 255.0f;
}

const float dae::InputManager::GetLeftStickX() const
{
	return HandleStick(ThumbStick::Left).x;
}

const float dae::InputManager::GetLeftStickY() const
{
	return HandleStick(ThumbStick::Left).y;
}

const float dae::InputManager::GetRightStickX() const
{
	return HandleStick(ThumbStick::Right).x;
}

const float dae::InputManager::GetRightStickY() const
{
	return HandleStick(ThumbStick::Right).y;
}

const glm::vec2 dae::InputManager::HandleStick(ThumbStick thumbstick) const
{
	glm::vec2 stick;
	float deadzone{};

	switch (thumbstick)
	{
	case dae::InputManager::ThumbStick::Left:
		stick.x = m_CurrentState.Gamepad.sThumbLX;
		stick.y = m_CurrentState.Gamepad.sThumbLY;
		deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		break;
	case dae::InputManager::ThumbStick::Right:
		stick.x = m_CurrentState.Gamepad.sThumbRX;
		stick.y = m_CurrentState.Gamepad.sThumbRY;
		deadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		break;
	default:
		break;
	}

	if (glm::length2(stick) < glm::pow(deadzone, 2))
		stick.x = stick.y = 0.f;
	else
	{
		float percentage = (glm::length(stick) - deadzone) / (m_MaxAxisValue - deadzone);
		stick = stick / glm::length(stick);
		stick *= percentage;
		glm::clamp(stick.x, -1.f, 1.f);
		glm::clamp(stick.y, -1.f, 1.f);
	}

	return stick;
}

#pragma endregion

#pragma region Keyboard

const bool dae::InputManager::IsPressed(const SDL_Scancode key) const
{
	return (m_CurrentKeyboardState[key] != 0);
}

const bool dae::InputManager::WasPressed(const SDL_Scancode key) const
{
	return (m_PreviousKeyboardState[key] != 0);
}

const dae::KeyState dae::InputManager::GetKeyState(const SDL_Scancode key) const
{
	if (WasPressed(key))
		if (IsPressed(key))
			return KeyState::Held;
		else
			return KeyState::Released;
	else
		if (IsPressed(key))
			return KeyState::Triggered;
		else
			return KeyState::Default;
}

const bool dae::InputManager::AreKeyModsPressed(const SDL_Keymod mod) const
{
	return (m_CurrentKeyMods & mod) != 0;
}

#pragma endregion
