#pragma once
#include <XInput.h>
#include "Singleton.h"

// TODO: Make it so you can actually add inputs to the InputManager..
// TODO: Make more than 1 controller available

namespace dae
{
	enum class ButtonState
	{
		Default,
		Triggered,
		Held,
		Released		
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		const bool IsPressed(const WORD button) const;
		const bool WasPressed(const WORD button) const;
		const ButtonState GetButtonState(const WORD button) const;

		const float GetLeftTrigger() const;
		const float GetRightTrigger() const;

		const float GetLeftStickX() const;
		const float GetLeftStickY() const;
		const float GetRightStickX() const;
		const float GetRightStickY() const;

	private:
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
	};
}
