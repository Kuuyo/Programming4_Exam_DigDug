#include "pch.h"
#include "DigDug.h"

#include "SceneManager.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "TextComponent.h"
#include "FPSComponent.h"

#include "Characters.h"

void DigDug::LoadGame() const
{
	dae::Scene* pTestScene = new dae::Scene("TestScene");
	dae::SceneManager::GetInstance().AddScene(pTestScene);

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextureComponent("background.jpg"));
	pTestScene->Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextureComponent("logo.png"));
	go->SetPosition(216, 180);
	pTestScene->Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextComponent("Programming 4 Assignment"));
	go->SetPosition(80, 20);
	pTestScene->Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::FPSComponent());
	go->SetPosition(3, 3);
	pTestScene->Add(go);

	////////////////////////////////////////////////////////////////////////////

	dae::Scene* pDigDugScene = new dae::Scene("DigDug");
	dae::SceneManager::GetInstance().AddScene(pDigDugScene);

	Prefabs::CreateDigDugCharacter(go = std::make_shared<dae::GameObject>());
	pDigDugScene->Add(go);
}
