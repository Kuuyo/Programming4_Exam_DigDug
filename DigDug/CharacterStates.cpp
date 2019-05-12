#include "pch.h"
#include "CharacterStates.h"

#include "GameContext.h"
#include "InputManager.h"
#include "GameObject.h"
#include "BodyComponent.h"
#include "GridComponent.h"

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
			if (gameContext.Input->GetInputMappingAxis("P1Horizontal") != 0.f
				|| gameContext.Input->GetInputMappingAxis("P1Vertical") != 0.f)
			{
				ChangeState<MovingState>();
				return;
			}

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
			float horizontal = gameContext.Input->GetInputMappingAxis("P1Horizontal");
			float vertical = gameContext.Input->GetInputMappingAxis("P1Vertical");

			if (horizontal == 0.f && vertical == 0.f)
			{
				ChangeState<IdleState>();
				return;
			}

			dae::Direction direction = (horizontal != 0.f)
				? (horizontal > 0.f) ? dae::Direction::Right : dae::Direction::Left
				: (vertical > 0.f) ? dae::Direction::Down : dae::Direction::Up;

			auto target = GetGameObject()->GetComponent<dae::GridComponent>()->GetClosestGridPointConstrained(direction);
			auto pos = GetGameObject()->GetPosition();

			GetGameObject()->GetComponent<dae::BodyComponent>()->MoveToTarget(target, 16.f);
		} // TODO: Easier access to BodyComponent?

		void MovingState::OnExit(const dae::GameContext &)
		{
			LogDebugC("");
			GetGameObject()->GetComponent<dae::BodyComponent>()->SetLinearVelocity(0.f, 0.f);
		}
	}
}