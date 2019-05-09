#include "pch.h"
#include "Level_1.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

#include "Characters.h"
#include "LevelBlocks.h"


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

	Prefabs::CreateDigDugCharacter(go = std::make_shared<dae::GameObject>());
	AddGameObject(go);

	Prefabs::CreateLevelBlock(go = std::make_shared<dae::GameObject>());
	go->SetPosition(216, 180);
	AddGameObject(go);
}

void Level_1::Update(const dae::GameContext &)
{
}
