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
		for (int i = 0; i < 4; ++i)
		{
			m_PreviousState[i] = m_CurrentState[i];

			ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));
			if (!XInputGetState(0, &m_CurrentState[i]) == ERROR_SUCCESS
				&& !m_bControllerIsDisconnected[i])
			{
				LogWarningC("No controller found at index " + std::to_string(i));
				m_bControllerIsDisconnected[i] = true;
			}
		}

		// InputMappings
		for (auto& im : m_InputMappingsVec)
		{
			// TODO: Handle cases where keyboard and controller used at same time
			// TODO: Keymods
			im.State = GetKeyState(im.PositiveKey);

			im.Axis = GetKeyAxis(im.PositiveKey, im.NegativeKey);

			if (im.HasGamePadButton && im.State == KeyState::Default)
				im.State = GetButtonState(im.GamePadButton, im.PlayerIndex);

			if (im.HasGamePadAxis && im.Axis == 0.f)
				im.Axis = GetAxis(im.GamePadAxis, im.PlayerIndex);
		}

		return true;
	}

	void InputManager::AddInputMapping(const InputMapping &inputMapping)
	{
		m_InputMappingsVec.push_back(inputMapping);
	}
	// TODO: Lots of copying going on, make some functions
	void InputManager::RemoveInputMapping(const std::string &inputMapping)
	{
		auto it = std::find_if(m_InputMappingsVec.begin(), m_InputMappingsVec.end(),
			[inputMapping](InputMapping im) { return im.Name == inputMapping; });

		if (it != m_InputMappingsVec.end())
			m_InputMappingsVec.erase(it);
	}

	const InputMapping InputManager::GetInputMappingStruct(const std::string &inputMapping) const
	{
		auto it = std::find_if(m_InputMappingsVec.begin(), m_InputMappingsVec.end(),
			[inputMapping](InputMapping im) { return im.Name == inputMapping; });

		if (it != m_InputMappingsVec.end())
			return (*it);
		else
			LogWarningC(inputMapping + std::string(" not found."));

		return InputMapping();
	}

	const KeyState InputManager::GetInputMappingState(const std::string &inputMapping) const
	{
		auto it = std::find_if(m_InputMappingsVec.begin(), m_InputMappingsVec.end(),
			[inputMapping](InputMapping im) { return im.Name == inputMapping; });

		if (it != m_InputMappingsVec.end())
			return (*it).State;
		else
			LogWarningC(inputMapping + std::string(" not found."));

		return KeyState::Default;
	}

	const float InputManager::GetInputMappingAxis(const std::string & inputMapping) const
	{
		auto it = std::find_if(m_InputMappingsVec.begin(), m_InputMappingsVec.end(),
			[inputMapping](InputMapping im) { return im.Name == inputMapping; });

		if (it != m_InputMappingsVec.end())
			return (*it).Axis;
		else
			LogWarningC(inputMapping + std::string(" not found."));

		return 0.f;
	}

#pragma region XInput

	const bool InputManager::IsPressed(const WORD button, unsigned int playerIndex) const
	{
		return (m_CurrentState[playerIndex].Gamepad.wButtons & button) != 0;
	}

	const bool InputManager::WasPressed(const WORD button, unsigned int playerIndex) const
	{
		return (m_PreviousState[playerIndex].Gamepad.wButtons & button) != 0;
	}

	const KeyState InputManager::GetButtonState(const WORD button, unsigned int playerIndex) const
	{
		if (WasPressed(button, playerIndex))
			if (IsPressed(button, playerIndex))
				return KeyState::Held;
			else
				return KeyState::Released;
		else
			if (IsPressed(button, playerIndex))
				return KeyState::Triggered;
			else
				return KeyState::Default;
	}

	const float InputManager::GetAxis(const GamePadAxis axis, unsigned int playerIndex) const
	{
		switch (axis)
		{
		case dae::GamePadAxis::None:
			return 0.f;
			break;
		case dae::GamePadAxis::LeftStickHorizontal:
			return GetLeftStickX(playerIndex);
			break;
		case dae::GamePadAxis::LeftStickVertical:
			return GetLeftStickY(playerIndex);
			break;
		case dae::GamePadAxis::RightStickHorizontal:
			return GetRightStickX(playerIndex);
			break;
		case dae::GamePadAxis::RightStickVertical:
			return GetRightStickY(playerIndex);
			break;
		case dae::GamePadAxis::LeftTrigger:
			return GetLeftTrigger(playerIndex);
			break;
		case dae::GamePadAxis::RightTrigger:
			return GetRightTrigger(playerIndex);
			break;
		case dae::GamePadAxis::LeftStickHorizontalAnalog:
			return GetLeftStickXAnalog(playerIndex);
			break;
		case dae::GamePadAxis::LeftStickVerticalAnalog:
			return GetLeftStickYAnalog(playerIndex);
			break;
		case dae::GamePadAxis::RightStickHorizontalAnalog:
			return GetRightStickXAnalog(playerIndex);
			break;
		case dae::GamePadAxis::RightStickVerticalAnalog:
			return GetRightStickYAnalog(playerIndex);
			break;
		default:
			return 0.f;
			break;
		}
	}

	const float InputManager::GetLeftTrigger(unsigned int playerIndex) const
	{
		return (float)m_CurrentState[playerIndex].Gamepad.bLeftTrigger / 255.0f;
	}

	const float InputManager::GetRightTrigger(unsigned int playerIndex) const
	{
		return (float)m_CurrentState[playerIndex].Gamepad.bRightTrigger / 255.0f;
	}

	const float InputManager::GetLeftStickX(unsigned int playerIndex) const
	{
		return HandleStickAxis(ThumbStick::LeftX, playerIndex);
	}
	
	const float InputManager::GetLeftStickY(unsigned int playerIndex) const
	{
		return HandleStickAxis(ThumbStick::LeftY, playerIndex);
	}
	
	const float InputManager::GetRightStickX(unsigned int playerIndex) const
	{
		return HandleStickAxis(ThumbStick::RightX, playerIndex);
	}
	
	const float InputManager::GetRightStickY(unsigned int playerIndex) const
	{
		return HandleStickAxis(ThumbStick::RightY, playerIndex);
	}

	const float InputManager::GetLeftStickXAnalog(unsigned int playerIndex) const
	{
		float value = HandleStickAxis(ThumbStick::LeftX, playerIndex);
		return (value > 0.f) ? glm::ceil(value) : glm::floor(value);
	}

	const float InputManager::GetLeftStickYAnalog(unsigned int playerIndex) const
	{
		float value = HandleStickAxis(ThumbStick::LeftY, playerIndex);
		return (value > 0.f) ? glm::ceil(value) : glm::floor(value);
	}

	const float InputManager::GetRightStickXAnalog(unsigned int playerIndex) const
	{
		float value = HandleStickAxis(ThumbStick::RightX, playerIndex);
		return (value > 0.f) ? glm::ceil(value) : glm::floor(value);
	}

	const float InputManager::GetRightStickYAnalog(unsigned int playerIndex) const
	{
		float value = HandleStickAxis(ThumbStick::RightY, playerIndex);
		return (value > 0.f) ? glm::ceil(value) : glm::floor(value);
	}

	const float InputManager::HandleStickAxis(const ThumbStick thumbstick, unsigned int playerIndex) const
	{
		float stickAxis{};
		float deadzone{};

		switch (thumbstick)
		{
		case dae::InputManager::ThumbStick::LeftX:
			stickAxis = m_CurrentState[playerIndex].Gamepad.sThumbLX;
			deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			break;
		case dae::InputManager::ThumbStick::LeftY:
			stickAxis = float(-m_CurrentState[playerIndex].Gamepad.sThumbLY);
			deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			break;
		case dae::InputManager::ThumbStick::RightX:
			stickAxis = m_CurrentState[playerIndex].Gamepad.sThumbRX;
			deadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			break;
		case dae::InputManager::ThumbStick::RightY:
			stickAxis = float(-m_CurrentState[playerIndex].Gamepad.sThumbRY);
			deadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			break;
		default:
			break;
		}

		if (glm::abs(stickAxis) < deadzone)
			stickAxis = 0.f;
		else
		{
			float percentage = (glm::abs(stickAxis) - deadzone) / (m_MaxAxisValue - deadzone);
			LogErrorC(std::to_string(percentage));
			stickAxis /= m_MaxAxisValue;
			stickAxis *= percentage;
			stickAxis = glm::clamp(stickAxis, -1.f, 1.f);
		}

		return stickAxis;
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

	const float InputManager::GetKeyAxis(const SDL_Scancode positiveKey, const SDL_Scancode negativeKey) const
	{
		float axis{ 0.f };

		if (positiveKey != SDL_SCANCODE_UNKNOWN)
			axis += IsPressed(positiveKey) ? 1.f : 0.f;

		if (negativeKey != SDL_SCANCODE_UNKNOWN)
			axis -= IsPressed(negativeKey) ? 1.f : 0.f;

		return axis;
	}

#pragma endregion

}