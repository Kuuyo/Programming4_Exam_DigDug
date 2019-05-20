#pragma once
#include <XInput.h>
#include <SDL_keycode.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "Observer.h"
#include "Structs.h"

// TODO: Make more than 1 controller available

namespace dae
{
	class InputManager final : public Subject
	{
	public:
		InputManager();
		~InputManager();

		bool ProcessInput();

		// InputMapping
		void AddInputMapping(const InputMapping &inputMapping);
		void RemoveInputMapping(const std::string &inputMapping);
		const InputMapping GetInputMappingStruct(const std::string &inputMapping) const;
		const KeyState GetInputMappingState(const std::string &inputMapping) const;
		const float GetInputMappingAxis(const std::string &inputMapping) const;

		// XInput
		const bool IsPressed(const WORD button, unsigned int playerIndex) const;
		const bool WasPressed(const WORD button, unsigned int playerIndex) const;
		const KeyState GetButtonState(const WORD button, unsigned int playerIndex) const;

		const float GetAxis(const GamePadAxis axis, unsigned int playerIndex) const;

		const float GetLeftTrigger(unsigned int playerIndex) const;
		const float GetRightTrigger(unsigned int playerIndex) const;

		const float GetLeftStickX(unsigned int playerIndex) const;
		const float GetLeftStickY(unsigned int playerIndex) const;
		const float GetRightStickX(unsigned int playerIndex) const;
		const float GetRightStickY(unsigned int playerIndex) const;

		const float GetLeftStickXAnalog(unsigned int playerIndex) const;
		const float GetLeftStickYAnalog(unsigned int playerIndex) const;
		const float GetRightStickXAnalog(unsigned int playerIndex) const;
		const float GetRightStickYAnalog(unsigned int playerIndex) const;

		// Keyboard
		const bool IsPressed(const SDL_Scancode key) const;
		const bool WasPressed(const SDL_Scancode key) const;
		const KeyState GetKeyState(const SDL_Scancode key) const;
		const bool AreKeyModsPressed(const SDL_Keymod mod) const;

		const float GetKeyAxis(const SDL_Scancode positiveKey, const SDL_Scancode negativeKey) const;

		InputManager(const InputManager&) = delete;
		InputManager(InputManager&&) = delete;
		InputManager& operator= (const InputManager&) = delete;
		InputManager& operator= (const InputManager&&) = delete;

	private:
		// XInput
		enum class ThumbStick
		{
			LeftX,
			LeftY,
			RightX,
			RightY
		};

		XINPUT_STATE m_CurrentState[4]{};
		XINPUT_STATE m_PreviousState[4]{};
		const float m_MaxAxisValue = 32767;
		bool m_bControllerIsDisconnected[4]{ false,false,false,false };

		const float HandleStickAxis(const ThumbStick thumbstick, unsigned int playerIndex) const;

		// Keyboard
		UINT8* m_pPreviousKeyboardState;
		const UINT8* m_pCurrentKeyboardState;
		SDL_Keymod m_PreviousKeyMods;
		SDL_Keymod m_CurrentKeyMods;

		// Mappings
		std::vector<InputMapping> m_InputMappingsVec;
	};
}
