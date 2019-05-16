#include "pch.h"
#include "Prefabs.h"

#include <GameObject.h>
#include <TextureComponent.h>
#include <BodyComponent.h>

#include "Characters.h"

namespace Prefabs
{
	unsigned short LevelBlock::m_CategoryBits = 0x0002;

	void LevelBlock::CreateLevelBlock(dae::GameObject* &out, const int blockSize)
	{
		if (out == nullptr)
			out = new dae::GameObject("LevelBlock");

		dae::BodyComponent* pBody = new dae::BodyComponent(b2BodyType::b2_staticBody);

		dae::BodyComponent::BoxFixtureDesc boxFixtureDesc{};
		boxFixtureDesc.halfWidth = blockSize * .5f;
		boxFixtureDesc.halfHeight = blockSize * .5f;
		boxFixtureDesc.isSensor = true;
		boxFixtureDesc.filter.categoryBits = m_CategoryBits;
		boxFixtureDesc.filter.maskBits = Characters::DigDug::GetCategoryBits();

		pBody->SetBoxFixture(boxFixtureDesc);

		out->AddComponent(pBody);

		SDL_Rect src{};
		src.h = src.w = blockSize;
		dae::TextureComponent* pTexture = new dae::TextureComponent("LevelBlock.gif", true, src);
		out->AddComponent(pTexture);
	}

	unsigned short Rock::m_CategoryBits = 0x0003;

	void Rock::CreateRock(dae::GameObject* &out, const int blockSize)
	{
		if (out == nullptr)
			out = new dae::GameObject("Rock");

		dae::BodyComponent* pBody = new dae::BodyComponent(b2BodyType::b2_staticBody);

		dae::BodyComponent::BoxFixtureDesc boxFixtureDesc{};
		boxFixtureDesc.halfWidth = blockSize * .5f;
		boxFixtureDesc.halfHeight = blockSize * .5f;
		boxFixtureDesc.isSensor = false;
		boxFixtureDesc.filter.categoryBits = m_CategoryBits;
		boxFixtureDesc.filter.maskBits = Characters::DigDug::GetCategoryBits();

		pBody->SetBoxFixture(boxFixtureDesc);

		out->AddComponent(pBody);

		SDL_Rect src{};
		src.h = src.w = blockSize;
		dae::TextureComponent* pTexture = new dae::TextureComponent("Rock.gif", true, src);
		out->AddComponent(pTexture);
	}
}



