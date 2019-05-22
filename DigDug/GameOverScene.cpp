#include "pch.h"
#include "GameOverScene.h"

#include <GameObject.h>
#include <TextComponent.h>
#include <InputManager.h>
#include <SceneManager.h>

GameOverScene::GameOverScene()
	: Scene("GameOverScene")
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize(const dae::SceneContext &)
{
	dae::GameObject* go = new dae::GameObject();
	go->AddComponent(new dae::TextComponent("GAME OVER", true, 36, SDL_Color({255,0,0})));
	AddGameObject(go);
	go->SetPosition(0.f, 50.f, dae::Anchor::TopCenter);

	go = new dae::GameObject();
	go->AddComponent(new dae::TextComponent("Press Space or (A)", true, 12));
	AddGameObject(go);
	go->SetPosition(0.f, 100.f, dae::Anchor::TopCenter);

	go = new dae::GameObject();
	go->AddComponent(new dae::TextComponent("to go back to Main Menu", true, 12));
	AddGameObject(go);
	go->SetPosition(0.f, 120.f, dae::Anchor::TopCenter);
}

void GameOverScene::Update(const dae::SceneContext &sceneContext)
{
	if (sceneContext.GameContext->Input->GetInputMappingState("Confirm") == dae::KeyState::Triggered)
	{
		sceneContext.GameContext->Scenes->SetActiveScene("MainMenu");
	}
}
