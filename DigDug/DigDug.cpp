#include "pch.h"
#include "DigDug.h"

#include "SceneManager.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "TextComponent.h"
#include "FPSComponent.h"

void DigDug::LoadGame() const
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextureComponent("background.jpg"));
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextureComponent("logo.png"));
	go->SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextComponent("Programming 4 Assignment"));
	go->SetPosition(80, 20);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::FPSComponent());
	go->SetPosition(3, 3);
	scene.Add(go);
}
