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
	go->AddComponent(new dae::TextureComponent("LevelBackground.png", false));
	AddGameObject(go);

	go = new dae::GameObject();
	go->AddComponent(new dae::FPSComponent(true, 16));
	AddGameObject(go);
	go->SetPosition(0.f, 6.f, dae::Anchor::BottomCenter);

	Characters::DigDug::CreateDigDugCharacter(m_pDigDug);
	AddGameObject(m_pDigDug);
	m_pDigDug->SetPosition(8.f, 24.f);

	Prefabs::CreateLevel("Level1.json", this, gameContext.GameSettings, gameContext);
}

void Level_1::Update(const dae::GameContext &)
{

}

void Level_1::OnCollisionEnter(const dae::Contact &contact, dae::GameObject* gameObject)
{
	// TODO: Predefine tags pls
	if (gameObject->GetTag() == "DigDug" && contact.Other->GetTag() == "LevelBlock")
	{
		RemoveGameObject(contact.Other);
	}
}

void Level_1::OnCollisionStay(const dae::Contact &, dae::GameObject* )
{
}

void Level_1::OnCollisionExit(const dae::Contact &, dae::GameObject* )
{
}
