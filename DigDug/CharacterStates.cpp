#include "pch.h"
#include "CharacterStates.h"

#include "GameContext.h"

namespace Characters
{
	namespace DigDug_States
	{
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

		void IdleState::Update(const dae::GameContext &)
		{
			LogDebugC("");
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

		void MovingState::Update(const dae::GameContext &)
		{
			LogDebugC("");
		}

		void MovingState::OnExit(const dae::GameContext &)
		{
			LogDebugC("");
		}
	}
}