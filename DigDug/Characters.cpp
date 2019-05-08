#include "pch.h"
#include "Characters.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "MovementComponent.h"
#include "BodyComponent.h"

void Prefabs::CreateDigDugCharacter(std::shared_ptr<dae::GameObject> out)
{
	if (out == nullptr)
		out = std::make_shared<dae::GameObject>();

	dae::BodyComponent* pBody = new dae::BodyComponent();
	dae::BodyComponent::BoxFixtureDesc fixtureDesc;
	ZeroMemory(&fixtureDesc, sizeof(fixtureDesc));
	fixtureDesc.halfWidth = 8.f;
	fixtureDesc.halfHeight = 8.f;
	pBody->SetBoxFixture(fixtureDesc);
	out->AddComponent(pBody);

	SDL_Rect src{};
	src.h = src.w = 16;
	dae::TextureComponent* pTexture = new dae::TextureComponent("DigDug.gif", true, src);
	out->AddComponent(pTexture);

	dae::MovementComponent* pMovement = new dae::MovementComponent();
	out->AddComponent(pMovement);
}
