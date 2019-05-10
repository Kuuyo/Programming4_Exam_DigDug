#include "pch.h"
#include "LevelBlocks.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "BodyComponent.h"
#include "Scene.h"
#include "GameContext.h"

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

void Prefabs::CreateLevel(dae::Scene* pScene, const dae::GameSettings &gameSettings, const int blockSize, const int topBorder, const int bottomBorder)
{
	dae::GameObject* go = nullptr;

	const float halfSize = blockSize * .5f;

	float x = -halfSize;
	float y = topBorder + halfSize;

	const int width = gameSettings.WindowResolutionW / blockSize;
	const int height = gameSettings.WindowResolutionH / blockSize
		- topBorder / blockSize
		- bottomBorder / blockSize;

	for (int i = 0; i < height; ++i)
	{
		x = -halfSize;
		for (int j = 0; j < width; ++j)
		{
			Prefabs::CreateLevelBlock(go = new dae::GameObject("LevelBlock"), blockSize);
			pScene->AddGameObject(go);
			x += blockSize;
			go->SetPosition(x, y);
		}
		y += blockSize;
	}
}