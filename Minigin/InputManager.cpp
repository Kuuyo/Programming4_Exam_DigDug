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
namespace dae
{
	InputManager::InputManager()
		: Subject("InputManager")
	{
		m_pPreviousKeyboardState = new UINT8[SDL_NUM_SCANCODES];
		m_pCurrentKeyboardState = SDL_GetKeyboardState(NULL);
	}

	InputManager::~InputManager()
	{
		delete[] m_pPreviousKeyboardState;
	}

	bool InputManager::ProcessInput()
	{
		// Keyboard
		memcpy(m_pPreviousKeyboardState, m_pCurrentKeyboardState, SDL_NUM_SCANCODES);

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				return false;
			if (e.type == SDL_KEYDOWN)
				Notify(this, 2, e.type, e.key);
			if (e.type == SDL_KEYUP)
				Notify(this, 2, e.type, e.key);
		}

		m_PreviousKeyMods = m_CurrentKeyMods;
		m_CurrentKeyMods = SDL_GetModState();

		// XInput
		m_PreviousState = m_CurrentState;

		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		if (!XInputGetState(0, &m_CurrentState) == ERROR_SUCCESS && !m_bControllerIsDisconnected)
		{
			LogWarningC("No controller found.");
			m_bControllerIsDisconnected = true;
		}

		// InputMappings
		for (auto& im : m_InputMappingsVec)
		{
			// TODO: Controller support
			im.State = GetKeyState(im.Key);
		}

		return true;
	}

	void InputManager::AddInputMapping(const InputMapping &inputMapping)
	{
		m_InputMappingsVec.push_back(inputMapping);
	}

	void InputManager::RemoveInputMapping(const std::string &inputMapping)
	{
		auto it = std::find_if(m_InputMappingsVec.begin(), m_InputMappingsVec.end(),
			[inputMapping](InputMapping im) { return im.Name == inputMapping; });

		if (it != m_InputMappingsVec.end())
			m_InputMappingsVec.erase(it);
	}

	const InputMapping InputManager::GetInputMapping(const std::string &inputMapping) const
	{
		auto it = std::find_if(m_InputMappingsVec.begin(), m_InputMappingsVec.end(),
			[inputMapping](InputMapping im) { return im.Name == inputMapping; });

		if (it != m_InputMappingsVec.end())
			return *it;
		else
			LogWarningC(inputMapping + std::string(" not found."));

		return InputMapping();
	}

	const KeyState InputManager::GetInputMappingState(const std::string & inputMapping) const
	{
		auto it = std::find_if(m_InputMappingsVec.begin(), m_InputMappingsVec.end(),
			[inputMapping](InputMapping im) { return im.Name == inputMapping; });

		if (it != m_InputMappingsVec.end())
			return (*it).State;
		else
			LogWarningC(inputMapping + std::string(" not found."));

		return KeyState::Default;
	}

#pragma region XInput

	const bool InputManager::IsPressed(const WORD button) const
	{
		return (m_CurrentState.Gamepad.wButtons & button) != 0;
	}

	const bool InputManager::WasPressed(const WORD button) const
	{
		return (m_PreviousState.Gamepad.wButtons & button) != 0;
	}

	const KeyState InputManager::GetButtonState(const WORD button) const
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

	const float InputManager::GetLeftTrigger() const
	{
		return (float)m_CurrentState.Gamepad.bLeftTrigger / 255.0f;
	}

	const float InputManager::GetRightTrigger() const
	{
		return (float)m_CurrentState.Gamepad.bRightTrigger / 255.0f;
	}

	const float InputManager::GetLeftStickX() const
	{
		return HandleStick(ThumbStick::Left).x;
	}

	const float InputManager::GetLeftStickY() const
	{
		return HandleStick(ThumbStick::Left).y;
	}

	const float InputManager::GetRightStickX() const
	{
		return HandleStick(ThumbStick::Right).x;
	}

	const float InputManager::GetRightStickY() const
	{
		return HandleStick(ThumbStick::Right).y;
	}

	const glm::vec2 InputManager::HandleStick(ThumbStick thumbstick) const
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

	const bool InputManager::IsPressed(const SDL_Scancode key) const
	{
		return (m_pCurrentKeyboardState[key] != 0);
	}

	const bool InputManager::WasPressed(const SDL_Scancode key) const
	{
		return (m_pPreviousKeyboardState[key] != 0);
	}

	const KeyState InputManager::GetKeyState(const SDL_Scancode key) const
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

	const bool InputManager::AreKeyModsPressed(const SDL_Keymod mod) const
	{
		return (m_CurrentKeyMods & mod) != 0;
	}

#pragma endregion

}