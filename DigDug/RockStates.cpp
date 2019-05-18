#include "pch.h"
#include "RockStates.h"

#include <GameContext.h>
#include <Box2D.h>
#include <GameObject.h>
#include <BodyComponent.h>
#include <Time.h>
#include <Box2DRaycastCallback.h>

namespace Level
{
	namespace RockEx
	{
		namespace States
		{
			IdleState::~IdleState() {}

			void IdleState::Initialize(const dae::GameContext &)
			{

			}

			void IdleState::OnEnter(const dae::GameContext &)
			{

			}

			void IdleState::Update(const dae::GameContext &gameContext)
			{
				dae::Box2DRaycastCallback callback;
				const auto pos = GetGameObject()->GetPosition();
				gameContext.Physics->RayCast(&callback, b2Vec2(pos.x, pos.y), b2Vec2(pos.x, pos.y + 8.f));

				if(callback.GetFixtures().size() == 0)
					ChangeState<WigglingState>();	
			}

			void IdleState::OnExit(const dae::GameContext &)
			{
				LogDebugC("");
			}



			WigglingState::~WigglingState(){}

			void WigglingState::Initialize(const dae::GameContext &)
			{
				m_ShakeElapsed = m_Duration / m_NumberOfShakes;
			}

			void WigglingState::OnEnter(const dae::GameContext &)
			{
				LogDebugC("");
			}

			void WigglingState::Update(const dae::GameContext &gameContext)
			{
				m_Timer += gameContext.Time->GetDeltaTime();

				const auto pos = GetGameObject()->GetPosition();
				
				if (m_Timer > m_ShakeElapsed)
				{
					GetGameObject()->SetPosition(pos.x +
						((m_CurrentAmountOfShakes % 2 == 0) ? m_ShakeOffset : -m_ShakeOffset)
						, pos.y);

					++m_CurrentAmountOfShakes;

					m_Timer -= m_ShakeElapsed;
				}

				if (m_CurrentAmountOfShakes == m_NumberOfShakes)
					ChangeState<FallingState>();
			}

			void WigglingState::OnExit(const dae::GameContext &)
			{
				LogDebugC("");
			}



			FallingState::~FallingState()
			{

			}

			void FallingState::Initialize(const dae::GameContext &)
			{

			}

			void FallingState::OnEnter(const dae::GameContext &)
			{
				GetGameObject()->GetComponent<dae::BodyComponent>()->SetType(b2BodyType::b2_dynamicBody);
				LogDebugC("");
			}

			void FallingState::Update(const dae::GameContext &)
			{
				auto pBody = GetGameObject()->GetComponent<dae::BodyComponent>();
				pBody->SetLinearVelocity(0.f, 48.f);

				auto contactList = GetGameObject()->GetComponent<dae::BodyComponent>()->GetContactList();
				if (contactList != nullptr)
				{
					auto tag = reinterpret_cast<dae::BodyComponent*>(contactList->other->GetUserData())->GetGameObject()->GetTag();
					if (tag == "DigDug" || tag == "LevelBlock")
					{
						ChangeState<BreakingState>();
						return;
					}
				}
			}

			void FallingState::OnExit(const dae::GameContext &)
			{

			}



			BreakingState::~BreakingState()
			{

			}

			void BreakingState::Initialize(const dae::GameContext &)
			{

			}

			void BreakingState::OnEnter(const dae::GameContext &)
			{
				auto pBody = GetGameObject()->GetComponent<dae::BodyComponent>();
				pBody->SetLinearVelocity(0.f, 0.f);
			}

			void BreakingState::Update(const dae::GameContext &)
			{
				// Do animation

				GetGameObject()->GetScene()->RemoveGameObject(GetGameObject());
			}

			void BreakingState::OnExit(const dae::GameContext &)
			{

			}
		}
	}
}