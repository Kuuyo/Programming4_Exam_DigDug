#include "pch.h"
#include "LevelBlocks.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "BodyComponent.h"

void Prefabs::CreateLevelBlock(std::shared_ptr<dae::GameObject> out)
{
	if (out == nullptr)
		out = std::make_shared<dae::GameObject>("LevelBlock");

	dae::BodyComponent* pBody = new dae::BodyComponent(b2BodyType::b2_kinematicBody);

	dae::BodyComponent::BoxFixtureDesc fixtureDesc{};
	fixtureDesc.halfWidth = 2.f;
	fixtureDesc.halfHeight = 2.f;
	fixtureDesc.isSensor = false;
	fixtureDesc.filter.categoryBits = 0x0002;
	fixtureDesc.filter.maskBits = 0x0001;
	// TODO: make bits not hardcoded

	std::vector<dae::BodyComponent::BoxFixtureDesc> boxFixtureDescs;
	fixtureDesc.center = { 2.f,2.f };
	boxFixtureDescs.push_back(fixtureDesc);
	fixtureDesc.center = { -2.f,-2.f };
	boxFixtureDescs.push_back(fixtureDesc);
	fixtureDesc.center = { 2.f,-2.f };
	boxFixtureDescs.push_back(fixtureDesc);
	fixtureDesc.center = { -2.f,2.f };
	boxFixtureDescs.push_back(fixtureDesc);

	pBody->SetBoxFixtures(boxFixtureDescs);

	out->AddComponent(pBody);

	SDL_Rect src{};
	src.h = src.w = 8;
	dae::TextureComponent* pTexture = new dae::TextureComponent("LevelBlock.gif", true, src);
	out->AddComponent(pTexture);
}