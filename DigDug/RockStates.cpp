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

			}

			void WigglingState::OnEnter(const dae::GameContext &)
			{
				LogDebugC("");
			}

			void WigglingState::Update(const dae::GameContext &gameContext)
			{
				m_Timer += gameContext.Time->GetDeltaTime();

				const auto pos = GetGameObject()->GetPosition();

				GetGameObject()->GetComponent<dae::BodyComponent>()->SetAngularVelocity(m_Timer);
			
				if (m_Timer > m_TimerMax)
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
				LogDebugC("");
			}

			void FallingState::Update(const dae::GameContext &)
			{
				GetGameObject()->GetComponent<dae::BodyComponent>()->SetLinearVelocity(0.f, 5.f);
			}

			void FallingState::OnExit(const dae::GameContext &)
			{

			}
		}
	}
}