#include "pch.h"
#include "Characters.h"
#include "CharacterStates.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "BodyComponent.h"
#include "GridComponent.h"

#include "FSMComponent.h"

namespace Characters
{
	unsigned short DigDug::m_CategoryBits = 0x001;

	void DigDug::CreateDigDugCharacter(dae::GameObject* &out)
	{
		if (out == nullptr)
			out = new dae::GameObject("DigDug");

		dae::BodyComponent::BoxFixtureDesc fixtureDesc{};
		fixtureDesc.halfWidth = 6.f;
		fixtureDesc.halfHeight = 6.f;
		fixtureDesc.filter.categoryBits = m_CategoryBits;
		// TODO: make bits not hardcoded
		dae::BodyComponent* pBody = new dae::BodyComponent();
		pBody->SetBoxFixture(fixtureDesc);
		out->AddComponent(pBody);

		SDL_Rect src{};
		src.h = src.w = 16;
		out->AddComponent(new dae::TextureComponent("DigDug.gif", true, src));

		// TODO: Make grid not hardcoded
		out->AddComponent(new dae::GridComponent(16, { 8.f,30.f }, 224, 256, true));

		dae::FSMComponent* pFSM = new dae::FSMComponent();
		pFSM->AddState(new DigDug_States::IdleState());
		pFSM->AddState(new DigDug_States::MovingState());
		out->AddComponent(pFSM);
	}
}