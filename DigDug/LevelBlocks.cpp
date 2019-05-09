#include "pch.h"
#include "LevelBlocks.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "BodyComponent.h"

void Prefabs::CreateLevelBlock(std::shared_ptr<dae::GameObject> out)
{
	if (out == nullptr)
		out = std::make_shared<dae::GameObject>();

	dae::BodyComponent* pBody = new dae::BodyComponent();

	dae::BodyComponent::BoxFixtureDesc fixtureDesc;
	ZeroMemory(&fixtureDesc, sizeof(fixtureDesc));
	fixtureDesc.halfWidth = 2.f;
	fixtureDesc.halfHeight = 2.f;
	fixtureDesc.isSensor = true;
	fixtureDesc.filter.categoryBits = 2;
	fixtureDesc.filter.maskBits = 2;

	std::vector<dae::BodyComponent::BoxFixtureDesc> boxFixtureDescs;
	fixtureDesc.center = { 1.f,1.f };
	boxFixtureDescs.push_back(fixtureDesc);
	fixtureDesc.center = { -1.f,-1.f };
	boxFixtureDescs.push_back(fixtureDesc);
	fixtureDesc.center = { 1.f,-1.f };
	boxFixtureDescs.push_back(fixtureDesc);
	fixtureDesc.center = { -1.f,1.f };
	boxFixtureDescs.push_back(fixtureDesc);

	pBody->SetBoxFixtures(boxFixtureDescs);

	out->AddComponent(pBody);

	SDL_Rect src{};
	src.h = src.w = 8;
	dae::TextureComponent* pTexture = new dae::TextureComponent("LevelBlock.gif", true, src);
	out->AddComponent(pTexture);
}