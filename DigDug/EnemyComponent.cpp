#include "pch.h"
#include "EnemyComponent.h"

#include <GameContext.h>
#include <Time.h>
#include <GameObject.h>
#include <AnimatedSpriteComponent.h>
#include <FSMComponent.h>
#include <Scene.h>

#include "Characters.h"
#include "FygarStates.h"

EnemyComponent::EnemyComponent()
{
}


bool EnemyComponent::Pump()
{
	++m_CurrentPumps;
	
	if (m_pSprite->GetActiveClipID() != to_integral(Characters::Fygar::AnimationClips::Ballooning))
	{
		m_pSprite->SetActiveClip(to_integral(Characters::Fygar::AnimationClips::Ballooning));
	}

	if (m_CurrentPumps >= m_MaxPumps)
	{
		m_pParent->GetComponent<dae::FSMComponent>()->
			ChangeState<Characters::FygarEx::States::DeathState>(m_pParent->GetScene()->GetSceneContext());
		return true;
	}
	else
	{
		m_pSprite->MoveOneFrame();
	}

	return false;
}

void EnemyComponent::Initialize(const dae::SceneContext &)
{
	m_pSprite = m_pParent->GetComponent<dae::AnimatedSpriteComponent>();
}

void EnemyComponent::Update(const dae::SceneContext &sceneContext)
{
	if (m_IsBeingPumped)
	{
		m_Timer += sceneContext.GameContext->Time->GetDeltaTime();

		if (m_Timer >= m_DeflationTime)
		{
			m_Timer -= m_DeflationTime;

			if (m_CurrentPumps > 0)
			{
				--m_CurrentPumps;
			}
		}
	}
}