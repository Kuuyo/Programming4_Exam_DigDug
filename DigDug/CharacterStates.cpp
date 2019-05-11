#include "pch.h"
#include "CharacterStates.h"

#include "GameContext.h"
#include "InputManager.h"

namespace Characters
{
	namespace DigDug_States
	{
		// TODO: Decide if checking input with if statements is what I want to do
		// As I can get Input with the Observer pattern too
		// But then all States are Observers and have an always active OnNotify
		// Maybe a bool to decide wether it uses the OnNotify or not ?
		// Make Minigin Observe and parse the info to send here to make it more readable?
		// As using the OnNotify here would be slightly obscure as it is implemented now
		// Another problem with all this though is that I'm not sure I would catch controller input then

		IdleState::~IdleState()
		{
		}

		void IdleState::Initialize(const dae::GameContext &)
		{
			LogDebugC("");
		}

		void IdleState::OnEnter(const dae::GameContext &)
		{
			LogDebugC("");
		}

		void IdleState::Update(const dae::GameContext &gameContext)
		{
			LogDebugC("");
			if (gameContext.Input->GetInputMappingAxis("P1Horizontal") != 0.f)
				ChangeState<MovingState>();
		}

		void IdleState::OnExit(const dae::GameContext &gameContext)
		{
			LogDebugC(gameContext.GameSettings.WindowTitle);
		}



		MovingState::~MovingState()
		{
		}

		void MovingState::Initialize(const dae::GameContext &)
		{
			LogDebugC("");
		}

		void MovingState::OnEnter(const dae::GameContext &)
		{
			LogDebugC("");
		}

		void MovingState::Update(const dae::GameContext &gameContext)
		{
			LogDebugC("");
			if (gameContext.Input->GetInputMappingAxis("P1Horizontal") == 0.f)
				ChangeState<IdleState>();
		}

		void MovingState::OnExit(const dae::GameContext &)
		{
			LogDebugC("");
		}
	}
}