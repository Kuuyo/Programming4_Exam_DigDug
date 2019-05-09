#include "pch.h"
#include "Level_1.h"

#include "GameObject.h"
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

void Level_1::Initialize(const dae::GameContext &)
{
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextureComponent("background.jpg", false));
	AddGameObject(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextureComponent("logo.png", false));
	go->SetPosition(216, 180);
	AddGameObject(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextComponent("Programming 4 Assignment"));
	go->SetPosition(80, 20);
	AddGameObject(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::FPSComponent());
	go->SetPosition(3, 3);
	AddGameObject(go);

	Prefabs::CreateDigDugCharacter(go = std::make_shared<dae::GameObject>("DigDug"));
	AddGameObject(go);

	go = std::make_shared<dae::GameObject>();
	dae::BodyComponent* pBody = new dae::BodyComponent();
	dae::BodyComponent::BoxFixtureDesc fixtureDesc{};
	fixtureDesc.halfWidth = 16.f;
	fixtureDesc.halfHeight = 16.f;

	pBody->SetBoxFixture(fixtureDesc);
	go->AddComponent(pBody);
	
	go = std::make_shared<dae::GameObject>("Wall");
	pBody = new dae::BodyComponent(b2BodyType::b2_staticBody);
	fixtureDesc.halfWidth = 10.f;
	fixtureDesc.halfHeight = 480.f;

	pBody->SetBoxFixture(fixtureDesc);
	
	go->AddComponent(pBody);
	go->SetPosition(300.f, 50.f);
	AddGameObject(go);

	Prefabs::CreateLevelBlock(go = std::make_shared<dae::GameObject>("LevelBlock"));
	go->SetPosition(216, 180);
	AddGameObject(go);
}

void Level_1::Update(const dae::GameContext &)
{
}

void Level_1::OnCollisionEnter(b2Contact*, dae::GameObject* gameObject)
{
	LogInfoC(gameObject->GetTag());
}

void Level_1::OnCollisionExit(b2Contact*, dae::GameObject* gameObject)
{
	LogInfoC(gameObject->GetTag());
}
