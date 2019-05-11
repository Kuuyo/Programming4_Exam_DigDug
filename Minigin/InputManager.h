#pragma once
#include <XInput.h>
#include <SDL_keycode.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "Observer.h"
#include "Structs.h"

// TODO: Make it so you can actually add inputs to the InputManager..
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
		const InputMapping GetInputMapping(const std::string &inputMapping) const;
		const KeyState GetInputMappingState(const std::string &inputMapping) const;

		// XInput
		const bool IsPressed(const WORD button) const;
		const bool WasPressed(const WORD button) const;
		const KeyState GetButtonState(const WORD button) const;

		const float GetLeftTrigger() const;
		const float GetRightTrigger() const;

		const float GetLeftStickX() const;
		const float GetLeftStickY() const;
		const float GetRightStickX() const;
		const float GetRightStickY() const;

		// Keyboard
		const bool IsPressed(const SDL_Scancode key) const;
		const bool WasPressed(const SDL_Scancode key) const;
		const KeyState GetKeyState(const SDL_Scancode key) const;
		const bool AreKeyModsPressed(const SDL_Keymod mod) const;

		InputManager(const InputManager&) = delete;
		InputManager(InputManager&&) = delete;
		InputManager& operator= (const InputManager&) = delete;
		InputManager& operator= (const InputManager&&) = delete;

	private:
		// XInput
		enum class ThumbStick
		{
			Left,
			Right
		};

		XINPUT_STATE m_CurrentState{};
		XINPUT_STATE m_PreviousState{};
		const float m_MaxAxisValue = 32767;
		bool m_bControllerIsDisconnected{ false };

		const glm::vec2 HandleStick(ThumbStick thumbstick) const;

		// Keyboard
		UINT8* m_pPreviousKeyboardState;
		const UINT8* m_pCurrentKeyboardState;
		SDL_Keymod m_PreviousKeyMods;
		SDL_Keymod m_CurrentKeyMods;

		// Mappings
		std::vector<InputMapping> m_InputMappingsVec;
	};
}
