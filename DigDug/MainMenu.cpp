#include "pch.h"
#include "MainMenu.h"

#include <GameObject.h>
#include <TextComponent.h>
#include <InputManager.h>
#include <SceneManager.h>

MainMenu::MainMenu()
	: Scene("MainMenu")
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::Initialize(const dae::SceneContext &)
{
	m_CurrentlySelected = 0;

	auto go = new dae::GameObject();
	go->AddComponent(new dae::TextComponent("Single Player"));
	AddGameObject(go);
	m_MenuSelectableObjects.push_back(go);

	go = new dae::GameObject();
	go->AddComponent(new dae::TextComponent("Co-op"));
	AddGameObject(go);
	go->SetPosition(0, 50);
	m_MenuSelectableObjects.push_back(go);

	go = new dae::GameObject();
	go->AddComponent(new dae::TextComponent("Versus"));
	AddGameObject(go);
	go->SetPosition(0, 100);
	m_MenuSelectableObjects.push_back(go);

	SelectGameObject(m_MenuSelectableObjects[m_CurrentlySelected]);
}

void MainMenu::Update(const dae::SceneContext &sceneContext)
{
	float axis = sceneContext.GameContext->Input->GetInputMappingAxis("P1Vertical");
	if (axis != 0.f && axis != m_PreviousAxis)
	{
		UnSelectGameObject(m_MenuSelectableObjects[m_CurrentlySelected]);
		m_CurrentlySelected += (int)axis;

		m_CurrentlySelected = (m_CurrentlySelected < 0) ?
			int(m_MenuSelectableObjects.size()) - 1 :
			m_CurrentlySelected % int(m_MenuSelectableObjects.size());
		
		SelectGameObject(m_MenuSelectableObjects[m_CurrentlySelected]);
	}
	m_PreviousAxis = axis;

	if (sceneContext.GameContext->Input->GetInputMappingState("Confirm") == dae::KeyState::Triggered)
	{
		const auto pSceneManager = sceneContext.GameContext->Scenes;

		switch (m_CurrentlySelected)
		{
		case 0:		
			pSceneManager->SetActiveScene("Level1_SP");
			break;
		case 1:
			pSceneManager->SetActiveScene("Level1_Coop");
			break;
		case 2:

			break;
		default:
			break;
		}
	}
}

void MainMenu::SelectGameObject(dae::GameObject* gameObject)
{
	gameObject->GetComponent<dae::TextComponent>()->SetColor({ 255,0,0 });
}

void MainMenu::UnSelectGameObject(dae::GameObject * gameObject)
{
	gameObject->GetComponent<dae::TextComponent>()->SetColor({ 255,255,255 });
}
