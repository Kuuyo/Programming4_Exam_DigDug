#include "pch.h"
#include "Characters.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "MovementComponent.h"
#include "BodyComponent.h"

void Prefabs::CreateDigDugCharacter(dae::GameObject* &out)
{
	if (out == nullptr)
		out = new dae::GameObject("DigDug");

	dae::BodyComponent* pBody = new dae::BodyComponent();
	dae::BodyComponent::BoxFixtureDesc fixtureDesc{};
	fixtureDesc.halfWidth = 5.f;
	fixtureDesc.halfHeight = 5.f;
	fixtureDesc.filter.categoryBits = 0x0001;
	// TODO: make bits not hardcoded

	pBody->SetBoxFixture(fixtureDesc);
	out->AddComponent(pBody);

	SDL_Rect src{};
	src.h = src.w = 16;
	dae::TextureComponent* pTexture = new dae::TextureComponent("DigDug.gif", true, src);
	out->AddComponent(pTexture);

	dae::MovementComponent* pMovement = new dae::MovementComponent(40);
	out->AddComponent(pMovement);
}