#include "pch.h"
#include "Prefabs.h"

#include <GameObject.h>
#include <TextureComponent.h>
#include <BodyComponent.h>
#include <FSMComponent.h>
#include <AnimatedSpriteComponent.h>
#include <GameContext.h>

#include "Characters.h"
#include "RockStates.h"

namespace Level
{
	unsigned short LevelBlock::m_CategoryBits = 0x0004;

	void LevelBlock::CreateLevelBlock(dae::GameObject* &out, const int blockSize)
	{
		if (out == nullptr)
			out = new dae::GameObject("LevelBlock");

		dae::BodyComponent* pBody = new dae::BodyComponent(b2BodyType::b2_staticBody);

		dae::BodyComponent::BoxFixtureDesc boxFixtureDesc{};
		boxFixtureDesc.halfWidth = blockSize * .5f;
		boxFixtureDesc.halfHeight = blockSize * .5f;
		// boxFixtureDesc.isSensor = true;
		boxFixtureDesc.filter.categoryBits = m_CategoryBits;
		boxFixtureDesc.filter.maskBits = Characters::DigDug::GetCategoryBits() | Rock::GetCategoryBits()
			| Characters::DigDug::GetPumpCategoryBits();

		pBody->SetBoxFixture(boxFixtureDesc);

		out->AddComponent(pBody);

		SDL_Rect src{};
		src.h = src.w = blockSize;
		dae::TextureComponent* pTexture = new dae::TextureComponent("LevelBlock.gif", true, src);
		out->AddComponent(pTexture);
	}

	unsigned short Rock::m_CategoryBits = 0x0008;

	void Rock::CreateRock(dae::GameObject* &out, const int blockSize)
	{
		if (out == nullptr)
			out = new dae::GameObject("Rock");

		dae::BodyComponent* pBody = new dae::BodyComponent(b2BodyType::b2_staticBody);

		dae::BodyComponent::BoxFixtureDesc boxFixtureDesc{};
		boxFixtureDesc.halfWidth = blockSize * .45f;
		boxFixtureDesc.halfHeight = blockSize * .45f;
		boxFixtureDesc.isSensor = false;
		boxFixtureDesc.filter.categoryBits = m_CategoryBits;
		boxFixtureDesc.filter.maskBits = Characters::DigDug::GetCategoryBits() | LevelBlock::GetCategoryBits();

		pBody->SetBoxFixture(boxFixtureDesc);

		out->AddComponent(pBody);

		dae::FSMComponent* pFSM = new dae::FSMComponent();
		pFSM->AddState(new RockEx::States::IdleState());
		pFSM->AddState(new RockEx::States::WigglingState());
		pFSM->AddState(new RockEx::States::FallingState());
		pFSM->AddState(new RockEx::States::BreakingState());
		out->AddComponent(pFSM);

		SDL_Rect src{};
		src.h = src.w = 16;
		auto animatedSpriteComponent = new dae::AnimatedSpriteComponent("Rock.gif", true, src, 2, 2, false);
		animatedSpriteComponent->AddClip(dae::AnimatedSpriteClip(to_integral(AnimationClips::Wiggle), 0, 2, 0.2f));
		animatedSpriteComponent->AddClip(dae::AnimatedSpriteClip(to_integral(AnimationClips::Break), 2, 2, 0.2f));
		animatedSpriteComponent->SetActiveClip(to_integral(AnimationClips::Wiggle));
		out->AddComponent(animatedSpriteComponent);
	}

	unsigned short BottomLayer::m_CategoryBits = 0x0016;

	void BottomLayer::CreateBottomLayer(dae::GameObject* &out, const dae::SceneContext &sceneContext, const int blockSize)
	{
		if (out == nullptr)
			out = new dae::GameObject("BottomLayer");

		dae::BodyComponent* pBody = new dae::BodyComponent(b2BodyType::b2_staticBody);

		dae::BodyComponent::BoxFixtureDesc boxFixtureDesc{};
		boxFixtureDesc.halfWidth = sceneContext.GameContext->GameSettings.WindowResolutionW * .5f;
		boxFixtureDesc.halfHeight = blockSize * .5f;
		boxFixtureDesc.isSensor = false;
		boxFixtureDesc.filter.categoryBits = m_CategoryBits;
		boxFixtureDesc.filter.maskBits = Rock::GetCategoryBits();

		pBody->SetBoxFixture(boxFixtureDesc);

		out->AddComponent(pBody);
	}
}



