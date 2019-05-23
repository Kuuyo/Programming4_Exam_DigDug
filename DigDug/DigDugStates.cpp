#include "pch.h"
#include "DigDugStates.h"

#include <GameContext.h>
#include <InputManager.h>
#include <GameObject.h>
#include <BodyComponent.h>
#include <GridComponent.h>
#include <AnimatedSpriteComponent.h>
#include <HealthComponent.h>
#include <SubjectComponent.h>
#include <Time.h>
#include <Scene.h>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/detail/func_common.hpp>
#pragma warning(pop)

#include "Characters.h"

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

			void GlobalState::Initialize(const dae::SceneContext &)
			{

			}

			void GlobalState::OnEnter(const dae::SceneContext &)
			{

			}

			void GlobalState::Update(const dae::SceneContext &)
			{
				if (!IsActiveState<DeathState>())
				{
					auto contactList = GetGameObject()->GetComponent<dae::BodyComponent>()->GetContactList();
					if (contactList != nullptr)
					{
						const auto tag = reinterpret_cast<dae::BodyComponent*>(contactList->other->GetUserData())->GetGameObject()->GetTag();
						LogDebugC(tag);
						if ((tag == "Rock" && contactList->other->GetType() == b2BodyType::b2_dynamicBody)
							|| tag == "Fygar")
						{
							auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();
							asc->SetActiveClip(to_integral(Characters::DigDug::AnimationClips::SquishH));
							asc->PlayOnce();

							ChangeState<DeathState>();
							return;
						}
					}
				}
			}

			void GlobalState::OnExit(const dae::SceneContext &)
			{

			}


			IdleState::IdleState(std::string &&hAxis, std::string &&vAxis)
				: m_HAxis(std::move(hAxis))
				, m_VAxis(std::move(vAxis))
			{
			}

			IdleState::~IdleState()
			{
			}

			void IdleState::Initialize(const dae::SceneContext &)
			{

			}

			void IdleState::OnEnter(const dae::SceneContext &)
			{
				auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();
				asc->SetActiveClip(to_integral(Characters::DigDug::AnimationClips::Walking));
				asc->Pause();
			}

			void IdleState::Update(const dae::SceneContext &sceneContext)
			{
				if (sceneContext.GameContext->Input->GetInputMappingAxis(m_HAxis) != 0.f
					|| sceneContext.GameContext->Input->GetInputMappingAxis(m_VAxis) != 0.f)
				{
					ChangeState<MovingState>();
					return;
				}
			}

			void IdleState::OnExit(const dae::SceneContext &)
			{

			}



			MovingState::MovingState(std::string &&hAxis, std::string &&vAxis)
				: m_HAxis(std::move(hAxis))
				, m_VAxis(std::move(vAxis))
			{
			}

			MovingState::~MovingState()
			{
			}

			void MovingState::Initialize(const dae::SceneContext &)
			{

			}

			void MovingState::OnEnter(const dae::SceneContext &)
			{
				auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();
				asc->SetActiveClip(to_integral(Characters::DigDug::AnimationClips::Walking));
				asc->Play();
			}

			void MovingState::Update(const dae::SceneContext &sceneContext)
			{
				float horizontal = sceneContext.GameContext->Input->GetInputMappingAxis(m_HAxis);
				float vertical = sceneContext.GameContext->Input->GetInputMappingAxis(m_VAxis);

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

				gameObject->GetComponent<dae::TransformComponent>()->SetOrientationX(vector.x);

				vector += pos;

				gameObject->GetComponent<dae::BodyComponent>()->MoveToTarget(vector, 32.f);
			}

			void MovingState::OnExit(const dae::SceneContext &)
			{
				GetGameObject()->GetComponent<dae::BodyComponent>()->SetLinearVelocity(0.f, 0.f);
				GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>()->Stop();
			} 



			void DeathState::Initialize(const dae::SceneContext &)
			{

			}

			void DeathState::OnEnter(const dae::SceneContext &)
			{
				auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();
				asc->SetActiveClip(to_integral(Characters::DigDug::AnimationClips::Dying));
				asc->PlayOnce();
			}

			void DeathState::Update(const dae::SceneContext &sceneContext)
			{
				const auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();

				if (!asc->IsPlaying())
				{
					asc->HideTexture();

					m_Timer += sceneContext.GameContext->Time->GetDeltaTime();
					if (m_Timer >= m_Duration)
					{
						auto health = GetGameObject()->GetComponent<dae::HealthComponent>();
						auto info = health->ChangeHealth(-1.f);
						GetGameObject()->GetComponent<dae::SubjectComponent>()->
							Notify(2, info, GetGameObject());
						if (info == dae::HealthStatus::Dead)
						{
							GetGameObject()->GetScene()->RemoveGameObject(GetGameObject());
						}
					}
				}
			}

			void DeathState::OnExit(const dae::SceneContext &)
			{
				m_Timer = 0.f;
			}
		}
	}
}

