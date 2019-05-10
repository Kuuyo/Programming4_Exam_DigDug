#include "pch.h"
#include "Characters.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "MovementComponent.h"
#include "BodyComponent.h"
#include "GridComponent.h"

void Prefabs::CreateDigDugCharacter(dae::GameObject* &out)
{
	if (out == nullptr)
		out = new dae::GameObject("DigDug");
	
	dae::BodyComponent::BoxFixtureDesc fixtureDesc{};
	fixtureDesc.halfWidth = 5.f;
	fixtureDesc.halfHeight = 5.f;
	fixtureDesc.filter.categoryBits = 0x0001;
	// TODO: make bits not hardcoded
	dae::BodyComponent* pBody = new dae::BodyComponent();
	pBody->SetBoxFixture(fixtureDesc);
	out->AddComponent(pBody);

	SDL_Rect src{};
	src.h = src.w = 16;
	out->AddComponent(new dae::TextureComponent("DigDug.gif", true, src));

	out->AddComponent(new dae::MovementComponent(40,false,true));

	out->AddComponent(new dae::GridComponent(8));
}