#include "pch.h"
#include "Characters.h"
#include "CharacterStates.h"

#include <GameObject.h>
#include <AnimatedSpriteComponent.h>
#include <BodyComponent.h>
#include <GridComponent.h>
#include <FSMComponent.h>
#include <HealthComponent.h>

namespace Characters
{
	unsigned short DigDug::m_CategoryBits = 0x001;

	void DigDug::CreateDigDugCharacter(dae::GameObject* &out)
	{
		if (out == nullptr)
			out = new dae::GameObject("DigDug");

		dae::BodyComponent::BoxFixtureDesc fixtureDesc{};
		fixtureDesc.halfWidth = 7.95f;
		fixtureDesc.halfHeight = 7.95f;
		fixtureDesc.filter.categoryBits = m_CategoryBits;
		dae::BodyComponent* pBody = new dae::BodyComponent(b2BodyType::b2_dynamicBody);
		pBody->SetBoxFixture(fixtureDesc);
		out->AddComponent(pBody);

		// TODO: Make grid not hardcoded
		out->AddComponent(new dae::GridComponent(16, { 8.f,24.f }, 224, 256, true));

		dae::FSMComponent* pFSM = new dae::FSMComponent();
		pFSM->AddState(new DigDugEx::States::IdleState());
		pFSM->AddState(new DigDugEx::States::MovingState());
		pFSM->AddState(new DigDugEx::States::DeathState());
		out->AddComponent(pFSM);

		SDL_Rect src{};
		src.h = src.w = 16;
		out->AddComponent(new dae::AnimatedSpriteComponent("DigDug.gif", true, src, 1, 2, 1.f / 10.f, false));

		out->AddComponent(new dae::HealthComponent(1.f, 3));
	}
}