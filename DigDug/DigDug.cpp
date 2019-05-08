#include "pch.h"
#include "DigDug.h"

#include "SceneManager.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "TextComponent.h"
#include "FPSComponent.h"

#include "Characters.h"

void DigDug::LoadGame(dae::GameContext gameContext) const
{
	dae::Scene* pTestScene = new dae::Scene("TestScene");
	gameContext.Scenes->AddScene(pTestScene);

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextureComponent("background.jpg", false));
	pTestScene->AddGameObject(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextureComponent("logo.png", false));
	go->SetPosition(216, 180);
	pTestScene->AddGameObject(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextComponent("Programming 4 Assignment"));
	go->SetPosition(80, 20);
	pTestScene->AddGameObject(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::FPSComponent());
	go->SetPosition(3, 3);
	pTestScene->AddGameObject(go);

	Prefabs::CreateDigDugCharacter(go = std::make_shared<dae::GameObject>());
	pTestScene->AddGameObject(go);

	////////////////////////////////////////////////////////////////////////////

	//dae::Scene* pDigDugScene = new dae::Scene("DigDug");
	//gameContext.Scenes->AddScene(pDigDugScene);
	//
	//Prefabs::CreateDigDugCharacter(go = std::make_shared<dae::GameObject>());
	//pDigDugScene->AddGameObject(go);
}
