#include "pch.h"
#include "RockStates.h"

#include <GameContext.h>
#include <Box2D.h>
#include <GameObject.h>
#include <BodyComponent.h>
#include <Time.h>
#include <Box2DRaycastCallback.h>
#include <AnimatedSpriteComponent.h>
#include <Scene.h>

#include "Prefabs.h"

namespace Level
{
	namespace RockEx
	{
		namespace States
		{
			IdleState::~IdleState() {}

			void IdleState::Initialize(const dae::SceneContext &)
			{

			}

			void IdleState::OnEnter(const dae::SceneContext &)
			{

			}

			void IdleState::Update(const dae::SceneContext &sceneContext)
			{
				dae::Box2DRaycastCallback callback;
				const auto pos = GetGameObject()->GetPosition();
				sceneContext.Physics->RayCast(&callback, b2Vec2(pos.x, pos.y), b2Vec2(pos.x, pos.y + 8.f));

				if(callback.GetFixtures().size() == 0)
					ChangeState<WigglingState>();	
			}

			void IdleState::OnExit(const dae::SceneContext &, State* )
			{

			}



			WigglingState::~WigglingState(){}

			void WigglingState::Initialize(const dae::SceneContext &)
			{
				m_ShakeElapsed = m_Duration / m_NumberOfShakes;
			}

			void WigglingState::OnEnter(const dae::SceneContext &)
			{
				auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();
				asc->SetActiveClip(to_integral(Level::Rock::AnimationClips::Wiggle));
				asc->Play();
			}

			void WigglingState::Update(const dae::SceneContext &sceneContext)
			{
				m_Timer += sceneContext.GameContext->Time->GetDeltaTime();

				const auto pos = GetGameObject()->GetPosition();
				
				if (m_Timer > m_ShakeElapsed)
				{
					++m_CurrentAmountOfShakes;

					m_Timer -= m_ShakeElapsed;
				}

				if (m_CurrentAmountOfShakes == m_NumberOfShakes)
					ChangeState<FallingState>();
			}

			void WigglingState::OnExit(const dae::SceneContext &, State* )
			{
				GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>()->Stop();
			}



			FallingState::~FallingState()
			{

			}

			void FallingState::Initialize(const dae::SceneContext &)
			{

			}

			void FallingState::OnEnter(const dae::SceneContext &)
			{
				GetGameObject()->GetComponent<dae::BodyComponent>()->SetType(b2BodyType::b2_dynamicBody);
			}

			void FallingState::Update(const dae::SceneContext &)
			{
				auto pBody = GetGameObject()->GetComponent<dae::BodyComponent>();
				pBody->SetLinearVelocity(0.f, 48.f);

				auto contactList = GetGameObject()->GetComponent<dae::BodyComponent>()->GetContactList();
				if (contactList != nullptr)
				{
					ChangeState<BreakingState>();
					return;
				}
			}

			void FallingState::OnExit(const dae::SceneContext &, State* )
			{

			}



			BreakingState::~BreakingState()
			{

			}

			void BreakingState::Initialize(const dae::SceneContext &)
			{

			}

			void BreakingState::OnEnter(const dae::SceneContext &)
			{
				auto pBody = GetGameObject()->GetComponent<dae::BodyComponent>();
				pBody->SetLinearVelocity(0.f, 0.f);

				auto asc = GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>();
				asc->SetActiveClip(to_integral(Level::Rock::AnimationClips::Break));
				asc->PlayOnce();
			}

			void BreakingState::Update(const dae::SceneContext &sceneContext)
			{
				if (!GetGameObject()->GetComponent<dae::AnimatedSpriteComponent>()->IsPlaying())
				{
					m_Timer += sceneContext.GameContext->Time->GetDeltaTime();
					if (m_Timer >= m_Duration)
					{
						GetGameObject()->GetScene()->RemoveGameObject(GetGameObject());
					}
				}
			}

			void BreakingState::OnExit(const dae::SceneContext &, State* )
			{

			}
		}
	}
}