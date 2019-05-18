#include "pch.h"
#include "CharacterStates.h"

#include <GameContext.h>
#include <InputManager.h>
#include <GameObject.h>
#include <BodyComponent.h>
#include <GridComponent.h>
#include <AnimatedSpriteComponent.h>

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

			}

			void IdleState::OnEnter(const dae::GameContext &)
			{
			}

			void IdleState::Update(const dae::GameContext &gameContext)
			{
				auto contactList = GetGameObject()->GetComponent<dae::BodyComponent>()->GetContactList();
				if (contactList != nullptr)
				{
					if (reinterpret_cast<dae::BodyComponent*>(contactList->other->GetUserData())->GetGameObject()->GetTag()
						== "Rock")
					{
						ChangeState<DeathState>();
						return;
					}
				}

				if (gameContext.Input->GetInputMappingAxis("P1Horizontal") != 0.f
					|| gameContext.Input->GetInputMappingAxis("P1Vertical") != 0.f)
				{
					ChangeState<MovingState>();
					return;
				}

			}

			void IdleState::OnExit(const dae::GameContext &)
			{

			}



			MovingState::~MovingState()
			{
			}

			void MovingState::Initialize(const dae::GameContext &)
			{

			}

			void MovingState::OnEnter(const dae::GameContext &)
			{
				GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>()->Play();
			}

			void MovingState::Update(const dae::GameContext &gameContext)
			{
				auto contactList = GetGameObject()->GetComponent<dae::BodyComponent>()->GetContactList();
				if (contactList != nullptr)
				{
					if (reinterpret_cast<dae::BodyComponent*>(contactList->other->GetUserData())->GetGameObject()->GetTag()
						== "Rock")
					{
						ChangeState<DeathState>();
						return;
					}
				}

				float horizontal = gameContext.Input->GetInputMappingAxis("P1Horizontal");
				float vertical = gameContext.Input->GetInputMappingAxis("P1Vertical");

				if (horizontal == 0.f && vertical == 0.f)
				{
					ChangeState<IdleState>();
					return;
				}

				glm::vec2 direction{ horizontal,vertical };

				if (direction.x != 0.f && direction.y != 0.f)
				{
					if (glm::abs(direction.x) < glm::abs(direction.y))
						direction.y = 0;
					else
						direction.x = 0;
				}

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

				gameObject->GetComponent<dae::BodyComponent>()->MoveToTarget(vector, 32.f);
			}

			void MovingState::OnExit(const dae::GameContext &)
			{
				GetGameObject()->GetComponent<dae::BodyComponent>()->SetLinearVelocity(0.f, 0.f);
				GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>()->Stop();
			} 



			void DeathState::Initialize(const dae::GameContext &)
			{

			}

			void DeathState::OnEnter(const dae::GameContext &)
			{

			}

			void DeathState::Update(const dae::GameContext &)
			{
				GetGameObject()->GetScene()->RemoveGameObject(GetGameObject());
			}

			void DeathState::OnExit(const dae::GameContext &)
			{

			}
}
	}
}