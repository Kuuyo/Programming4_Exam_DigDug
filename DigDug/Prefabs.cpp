#include "pch.h"
#include "Prefabs.h"

#include <json.hpp>
#include <GameObject.h>
#include <TextureComponent.h>
#include <BodyComponent.h>
#include <Scene.h>
#include <GameContext.h>
#include <ResourceManager.h>

void Prefabs::CreateLevelBlock(dae::GameObject* &out, const int blockSize)
{
	if (out == nullptr)
		out = new dae::GameObject("LevelBlock");

	dae::BodyComponent* pBody = new dae::BodyComponent(b2BodyType::b2_staticBody);
	
	dae::BodyComponent::BoxFixtureDesc boxFixtureDesc{};
	boxFixtureDesc.halfWidth = blockSize * .5f;
	boxFixtureDesc.halfHeight = blockSize * .5f;
	boxFixtureDesc.isSensor = true;
	boxFixtureDesc.filter.categoryBits = 0x0002;
	boxFixtureDesc.filter.maskBits = 0x0001;
	// TODO: make bits not hardcoded
	
	pBody->SetBoxFixture(boxFixtureDesc);
	
	out->AddComponent(pBody);

	SDL_Rect src{};
	src.h = src.w = blockSize;
	dae::TextureComponent* pTexture = new dae::TextureComponent("LevelBlock.gif", true, src);
	out->AddComponent(pTexture);
}

