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
	fixtureDesc.halfWidth = 5.f;
	fixtureDesc.halfHeight = 5.f;
	pBody->SetBoxFixture(fixtureDesc);
	out->AddComponent(pBody);

	dae::TextureComponent* pTexture = new dae::TextureComponent("DigDug.gif");
	out->AddComponent(pTexture);

	dae::MovementComponent* pMovement = new dae::MovementComponent();
	out->AddComponent(pMovement);
}
