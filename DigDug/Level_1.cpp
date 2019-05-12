#include "pch.h"
#include "Level_1.h"

#include "InputManager.h"

#include "GameObject.h"
#include "GameContext.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "BodyComponent.h"

#include "Characters.h"
#include "LevelBlocks.h"

#include <Box2D.h>


Level_1::Level_1()
	: Scene("Level_1")
{
}


Level_1::~Level_1()
{
}

void Level_1::Initialize(const dae::GameContext &gameContext)
{
	auto go = new dae::GameObject();
	go->AddComponent(new dae::TextureComponent("DigDug.png", false));
	AddGameObject(go);

	go = new dae::GameObject();
	go->AddComponent(new dae::FPSComponent(true, 16));
	AddGameObject(go);
	go->SetPosition(0.f, 6.f, dae::Anchor::BottomCenter);

	Characters::DigDug::CreateDigDugCharacter(m_pDigDug);
	AddGameObject(m_pDigDug);
	m_pDigDug->SetPosition(10.f, 10.f);
	
	// TODO: Make Wall prefab
	go = new dae::GameObject("Wall");
	dae::BodyComponent::BoxFixtureDesc fixtureDesc{};
	auto pBody = new dae::BodyComponent(b2BodyType::b2_staticBody);
	fixtureDesc.halfWidth = .1f;
	fixtureDesc.halfHeight = float(gameContext.GameSettings.WindowHeight * .5f);

	pBody->SetBoxFixture(fixtureDesc);
	
	go->AddComponent(pBody);
	AddGameObject(go);
	go->SetPosition(float(gameContext.GameSettings.WindowResolutionW + .1f)
		, float(gameContext.GameSettings.WindowHeight * .5f));

	// Prefabs::CreateLevel(this, gameContext.GameSettings, 8);
}

void Level_1::Update(const dae::GameContext &)
{

}

void Level_1::OnCollisionEnter(b2Contact* contact, dae::GameObject* gameObject)
{
	// TODO: Predefine tags pls
	if (gameObject->GetTag() == "DigDug" &&
		static_cast<dae::BodyComponent*>( // TODO: wtf, fix this
			contact->GetFixtureB()->GetUserData())->GetGameObject()->GetTag() == "LevelBlock")
	{
		RemoveGameObject(static_cast<dae::BodyComponent*>( // TODO: wtf, fix this
			contact->GetFixtureB()->GetUserData())->GetGameObject());
	}
}

void Level_1::OnCollisionStay(b2Contact*, dae::GameObject* )
{
}

void Level_1::OnCollisionExit(b2Contact*, dae::GameObject* )
{
}
