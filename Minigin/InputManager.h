#pragma once
#include <XInput.h>
#include "Singleton.h"

// TODO: Make it so you can actually add inputs to the InputManager..

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
	private:
		XINPUT_STATE currentState{};
	};

}
