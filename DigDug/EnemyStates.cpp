#include "pch.h"
#include "EnemyStates.h"

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
#include <Box2DRaycastCallback.h>
#include <HelperFunctions.h>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/detail/func_common.hpp>
#pragma warning(pop)

#include "Characters.h"
#include "EnemyComponent.h"

namespace Characters
{
	namespace EnemyEx
	{
		namespace States
		{
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
						const auto tag = reinterpret_cast<dae::BodyComponent*>(contactList->other->GetUserData())->
							GetGameObject()->GetTag();
						if (tag == "Rock" && contactList->other->GetType() == b2BodyType::b2_dynamicBody)
						{
							auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();
							asc->SetActiveClip(to_integral(Characters::Enemy::AnimationClips::Squish));
							asc->PlayOnce();

							ChangeState<DeathState>();
							return;
						}
					}
				}
			}

			void GlobalState::OnExit(const dae::SceneContext &, State* )
			{

			}


			MovingState::MovingState()
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
				asc->SetActiveClip(to_integral(Characters::Enemy::AnimationClips::Walking));
				asc->Play();

				m_RandomGhostInterval = dae::Random::GetRandomFloat(3.f, 9.f);
				m_RandomInterval = dae::Random::GetRandomFloat(3.f, 6.f);
			}

			void MovingState::Update(const dae::SceneContext &sceneContext)
			{
				const auto deltaTime = sceneContext.GameContext->Time->GetDeltaTime();
				m_Timer += deltaTime;
				m_GhostTimer += deltaTime;

				if (m_GhostTimer > m_RandomGhostInterval)
				{
					ChangeState<GhostState>();
					return;
				}

				if (m_Timer > m_RandomInterval)
				{
					m_RandomInterval = dae::Random::GetRandomFloat(3.f, 6.f);
					m_Horizontal = dae::Random::GetRandomFloat(-1.f, 1.f);
					m_Vertical = dae::Random::GetRandomFloat(-1.f, 1.f);
					m_Timer = 0.f;
				}

				if (m_Horizontal == 0.f && m_Vertical == 0.f)
				{
					m_Horizontal = 1.f;
				}

				// TODO: This might be a little overkill ?
				dae::Box2DRaycastCallback callback;
				const auto pos = GetGameObject()->GetPosition();
				sceneContext.Physics->RayCast(&callback, b2Vec2(pos.x, pos.y),
					b2Vec2(pos.x + m_Horizontal * 8.f, pos.y + m_Vertical * 8.f));

				auto fixt = callback.GetFixtures();

				for (const auto& f : fixt)
				{
					const auto tag = reinterpret_cast<dae::BodyComponent*>(f->GetUserData())->GetGameObject()->GetTag();
					if (tag == "LevelBlock" || tag == "Rock")
					{
						m_Horizontal = -m_Horizontal;
						m_Vertical = -m_Vertical;
						break;
					}
				}

				glm::vec2 direction{ m_Horizontal,m_Vertical };

				if (direction.x != 0.f && direction.y != 0.f)
				{
					if (glm::abs(direction.x) < glm::abs(direction.y))
						direction.y = 0;
					else
						direction.x = 0;
				}

				auto gameObject = GetGameObject();

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

				gameObject->GetComponent<dae::BodyComponent>()->MoveToTarget(vector, 40.f);
			}

			void MovingState::OnExit(const dae::SceneContext &, State* )
			{
				GetGameObject()->GetComponent<dae::BodyComponent>()->SetLinearVelocity(0.f, 0.f);
				GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>()->Stop();

				m_GhostTimer = 0.f;
				m_Timer = 0.f;
			}


			void GhostState::Initialize(const dae::SceneContext &)
			{
				m_pEnemyComponent = GetGameObject()->GetComponent<EnemyComponent>();
			}

			void GhostState::OnEnter(const dae::SceneContext &)
			{
				auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();
				asc->SetActiveClip(to_integral(Characters::Enemy::AnimationClips::Ghosting));
				asc->Play();
			}

			void GhostState::Update(const dae::SceneContext &sceneContext)
			{
				m_Timer += sceneContext.GameContext->Time->GetDeltaTime();

				if (m_Timer > m_MinGhostTime)
				{
					bool isInLevel{ true };

					auto fix = GetGameObject()->GetComponent<dae::BodyComponent>()->GetContactList();
					while (fix != nullptr)
					{
						const auto tag = reinterpret_cast<dae::BodyComponent*>(fix->other->GetUserData())->
							GetGameObject()->GetTag();

						if (tag == "LevelBlock")
						{
							isInLevel = false;
						}

						fix = fix->next;
					}

					if (isInLevel)
					{
						GetGameObject()->SetPosition(GetGameObject()->GetComponent<dae::GridComponent>()->
							SnapToGrid(GetGameObject()->GetPosition()));
						ChangeState<MovingState>();
						return;
					}
				}

				const auto playerPos = m_pEnemyComponent->GetPlayer()->GetPosition();
				GetGameObject()->GetComponent<dae::BodyComponent>()->MoveToTarget(playerPos, 40.f);
			}

			void GhostState::OnExit(const dae::SceneContext &, State *)
			{
				GetGameObject()->GetComponent<dae::BodyComponent>()->SetLinearVelocity(0.f, 0.f);
			}


			void HitState::Initialize(const dae::SceneContext &)
			{

			}

			void HitState::OnEnter(const dae::SceneContext &)
			{
				auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();
				asc->SetActiveClip(to_integral(Characters::Enemy::AnimationClips::Pumped));
				asc->PlayOnce();
			}

			void HitState::Update(const dae::SceneContext &)
			{

			}

			void HitState::OnExit(const dae::SceneContext &, State* )
			{

			}



			void DeathState::Initialize(const dae::SceneContext &)
			{

			}

			void DeathState::OnEnter(const dae::SceneContext &)
			{
				GetGameObject()->GetComponent<dae::BodyComponent>()->RemoveFixtures();
			}

			void DeathState::Update(const dae::SceneContext &sceneContext)
			{
				const auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();

				if (!asc->IsPlaying())
				{
					m_Timer += sceneContext.GameContext->Time->GetDeltaTime();
					if (m_Timer >= m_Duration)
					{
						GetGameObject()->GetScene()->RemoveGameObject(GetGameObject());
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