#include "pch.h"
#include "CharacterStates.h"

#include "GameContext.h"
#include "InputManager.h"
#include "GameObject.h"
#include "BodyComponent.h"
#include "GridComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/detail/func_common.hpp>
#pragma warning(pop)

namespace Characters
{
	namespace DigDugEx
	{
		namespace States
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

				glm::vec2 direction{ horizontal,vertical };

				LogFormatC(dae::LogLevel::Warning, "Direction: %f, %f", direction.x, direction.y);

				if (direction.x != 0.f && direction.y != 0.f)
				{
					if (glm::abs(direction.x) < glm::abs(direction.y))
						direction.y = 0;
					else
						direction.x = 0;
				}

				LogFormatC(dae::LogLevel::Warning, "Direction2: %f, %f", direction.x, direction.y);

				auto gameObject = GetGameObject();

				auto pos = gameObject->GetPosition();
				auto target = gameObject->GetComponent<dae::GridComponent>()->GetNextGridPoint(pos, direction);

				auto vector = target - pos;

				if (vector.x != 0.f && vector.y != 0.f)
				{
					if (glm::abs(vector.x) < glm::abs(vector.y))
						vector.y = 0;
					else
						vector.x = 0;
				}

				vector += pos;

				LogFormatC(dae::LogLevel::Debug, "Pos: %f, %f", pos.x, pos.y);
				LogFormatC(dae::LogLevel::Debug, "Target: %f, %f", target.x, target.y);
				LogFormatC(dae::LogLevel::Debug, "MoveToTarget: %f, %f", vector.x, vector.y);

				gameObject->GetComponent<dae::BodyComponent>()->MoveToTarget(vector, 32.f);
			} // TODO: Easier access to BodyComponent?

			void MovingState::OnExit(const dae::GameContext &)
			{
				LogDebugC("");
				GetGameObject()->GetComponent<dae::BodyComponent>()->SetLinearVelocity(0.f, 0.f);
			} 
		}
	}
}