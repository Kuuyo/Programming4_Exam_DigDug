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
#include <GameTime.h>
#include <Scene.h>
#include <TextureComponent.h>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/detail/func_common.hpp>
#pragma warning(pop)

#include "Characters.h"
#include "Prefabs.h"
#include "EnemyStates.h"
#include "EnemyComponent.h"

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

			void GlobalState::Update(const dae::SceneContext &sceneContext)
			{
				if (!IsActiveState<DeathState>())
				{
					auto contactList = GetGameObject()->GetComponent<dae::BodyComponent>()->GetContactList();
					if (contactList != nullptr)
					{
						const auto gameObject = reinterpret_cast<dae::BodyComponent*>(contactList->other->GetUserData())->GetGameObject();
						const auto tag = gameObject->GetTag();
						LogDebugC(tag);
						if ((tag == "Rock" && contactList->other->GetType() == b2BodyType::b2_dynamicBody))
						{
							ChangeState<SquishState>();
							return;
						}
						else if (tag == "Fygar")
						{
							ChangeState<DeathState>();
							return;
						}
						else if (tag == "LevelBlock")
						{
							gameObject->GetScene()->RemoveGameObject(gameObject);
						}
					}

					if (!IsActiveState<ThrowPumpState>() && !IsActiveState<PumpingState>())
					{
						if (sceneContext.GameContext->Input->GetInputMappingAxis(GetState<ThrowPumpState>()->GetPumpMapping()))
						{
							ChangeState<ThrowPumpState>();
							return;
						}
					}
				}
			}

			void GlobalState::OnExit(const dae::SceneContext &, State* )
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

			void IdleState::OnExit(const dae::SceneContext &, State* )
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

				gameObject->SetOrientationX(vector.x);

				vector += pos;

				gameObject->GetComponent<dae::BodyComponent>()->MoveToTarget(vector, 32.f);
			}

			void MovingState::OnExit(const dae::SceneContext &, State* )
			{
				GetGameObject()->GetComponent<dae::BodyComponent>()->SetLinearVelocity(0.f, 0.f);
				GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>()->Stop();
			} 



			ThrowPumpState::ThrowPumpState(std::string &&pumpMapping)
				: m_PumpMapping(std::move(pumpMapping))
			{
			}

			void ThrowPumpState::Initialize(const dae::SceneContext &)
			{
				m_pPump = GetGameObject()->GetChild(0); // TODO: This can give some problems
				m_pBody = m_pPump->GetComponent<dae::BodyComponent>();
				m_pTexture = m_pPump->GetComponent<dae::TextureComponent>();
				m_OriginalLocalPos = m_pPump->GetLocalPosition();
			}

			void ThrowPumpState::OnEnter(const dae::SceneContext &)
			{
				auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();
				asc->SetActiveClip(to_integral(Characters::DigDug::AnimationClips::ThrowPump));
				asc->PlayOnce();

				m_HalfWidth = 0.f;
				m_pPump->SetLocalPosition(m_OriginalLocalPos);
			}

			void ThrowPumpState::Update(const dae::SceneContext &sceneContext)
			{
				auto contactList = m_pBody->GetContactList();

				if (contactList != nullptr)
				{
					const auto gameObject = reinterpret_cast<dae::BodyComponent*>(contactList->other->GetUserData())->GetGameObject();
					const auto tag = gameObject->GetTag();
					if (tag != "Fygar")
					{
						ChangeState<IdleState>();
						return;
					}
					else
					{
						// TODO: Figure out why it doesn't work in FygarStates, since this is kinda very dirty
   						gameObject->GetComponent<dae::FSMComponent>()->ChangeState<EnemyEx::States::HitState>(sceneContext);
						m_EnemyHit = gameObject;
						ChangeState<PumpingState>();
						return;
					}
				}

				if (!sceneContext.GameContext->Input->GetInputMappingAxis(m_PumpMapping)
					|| m_HalfWidth >= 16.f)
				{
					ChangeState<IdleState>();
					return;
				}

				m_HalfWidth += sceneContext.GameContext->Time->GetDeltaTime() * 16.f;

				dae::BodyComponent::BoxFixtureDesc fixtureDesc;
				fixtureDesc.halfWidth = m_HalfWidth;
				fixtureDesc.halfHeight = 4.f;
				fixtureDesc.filter.categoryBits = Characters::DigDug::GetPumpCategoryBits();
				fixtureDesc.filter.maskBits = Level::Rock::GetCategoryBits() | Level::LevelBlock::GetCategoryBits() |
					Enemy::GetCategoryBits();

				m_pBody->RemoveFixtures();
				m_pBody->SetBoxFixture(fixtureDesc);
				m_pPump->SetLocalPosition(m_OriginalLocalPos.x + m_HalfWidth, m_OriginalLocalPos.y);

				SDL_Rect src{};
				src.y = 96;
				src.h = 16;
				src.w = int(glm::round(m_HalfWidth * 2));
				src.x = 32 - src.w;
				m_pTexture->SetSourceRect(src);
			}

			void ThrowPumpState::OnExit(const dae::SceneContext &, State* pNextState)
			{
				m_pBody->RemoveFixtures();

				if (pNextState != GetState<PumpingState>())
				{
					SDL_Rect src{};
					src.y = 96;
					src.h = -1;
					src.w = -1;
					m_pTexture->SetSourceRect(src);
				}
				else
				{
					GetState<PumpingState>()->m_EnemyHit = m_EnemyHit;
					m_EnemyHit = nullptr;
				}
			}



			PumpingState::PumpingState(std::string &&pumpMapping)
				: m_PumpMapping(std::move(pumpMapping))
			{
			}

			void PumpingState::Initialize(const dae::SceneContext &)
			{
				m_pPump = GetGameObject()->GetChild(0); // TODO: This can give some problems
				m_pBody = m_pPump->GetComponent<dae::BodyComponent>();
				m_pTexture = m_pPump->GetComponent<dae::TextureComponent>();
			}

			void PumpingState::OnEnter(const dae::SceneContext &)
			{
				auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();
				asc->SetActiveClip(to_integral(Characters::DigDug::AnimationClips::Pumping));
				asc->Pause();
			}

			void PumpingState::Update(const dae::SceneContext &sceneContext)
			{
				auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();

				if (sceneContext.GameContext->Input->GetInputMappingAxis(m_PumpMapping))
				{
					asc->PlayOnce();
					m_Timer += sceneContext.GameContext->Time->GetDeltaTime();

					if (m_Timer >= m_PumpInterval)
					{
						m_Timer -= m_PumpInterval;
						if (m_EnemyHit->GetComponent<EnemyComponent>()->Pump())
						{
							ChangeState<IdleState>();
						}
					}
				}
				else
				{
					asc->Pause();
					m_Timer = 0.f;
				}
			}

			void PumpingState::OnExit(const dae::SceneContext &, State* )
			{
				SDL_Rect src{};
				src.y = 96;
				src.h = -1;
				src.w = -1;
				m_pTexture->SetSourceRect(src);

				m_EnemyHit = nullptr;
			}



			void SquishState::Initialize(const dae::SceneContext &)
			{

			}

			void SquishState::OnEnter(const dae::SceneContext &)
			{
				auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();
				asc->SetActiveClip(to_integral(Characters::DigDug::AnimationClips::SquishH));
				asc->PlayOnce();
			}

			void SquishState::Update(const dae::SceneContext &sceneContext)
			{
				const auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();

				if (!asc->IsPlaying())
				{
					m_Timer += sceneContext.GameContext->Time->GetDeltaTime();
					if (m_Timer >= m_Duration)
					{
						ChangeState<DeathState>();
					}
				}
			}

			void SquishState::OnExit(const dae::SceneContext &, State*)
			{

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

			void DeathState::OnExit(const dae::SceneContext &, State* )
			{
				m_Timer = 0.f;
			}
		}
	}
}

