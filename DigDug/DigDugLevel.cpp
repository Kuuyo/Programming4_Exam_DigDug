#include "pch.h"
#include "DigDugLevel.h"

#include <GameObject.h>
#include <TextureComponent.h>
#include <FPSComponent.h>
#include <ResourceManager.h>
#include <HealthComponent.h>
#include <SubjectComponent.h>
#include <FSMComponent.h>
#include <SceneManager.h>

#include <json.hpp>

#include "Prefabs.h"
#include "Characters.h"
#include "DigDugStates.h"

DigDugLevel::DigDugLevel(std::string &&sceneName, std::string &&levelName, const GameMode gameMode)
	: Scene(sceneName)
	, m_LevelName(std::move(levelName))
	, m_GameMode(gameMode)
{
}


DigDugLevel::~DigDugLevel()
{
}

void DigDugLevel::Initialize(const dae::SceneContext &sceneContext)
{
	m_pDigDug = nullptr;
	m_pDigDug2 = nullptr;

	// Background
	auto go = new dae::GameObject();
	go->AddComponent(new dae::TextureComponent("LevelBackground.png", false));
	AddGameObject(go);

	// FPS
	go = new dae::GameObject();
	go->AddComponent(new dae::FPSComponent(true, 16));
	AddGameObject(go);
	go->SetPosition(0.f, 6.f, dae::Anchor::BottomCenter);

	// Level
	nlohmann::json jsonLevel = sceneContext.GameContext->Resources->LoadJson(m_LevelName + ".json");
	auto layout = jsonLevel["layout"];

	std::vector<LevelSectionType> levelVec;
	levelVec.reserve(layout.size());

	for (auto it = layout.begin(); it != layout.end(); ++it)
	{
		levelVec.push_back(it.value());
	}

	const int blockSize = 16;
	const int topBorder = 32;
	const int bottomBorder = 16;

	const float halfSize = blockSize * .5f;

	float x = 0;
	float y = topBorder + halfSize;

	const int width = sceneContext.GameContext->GameSettings.WindowResolutionW / blockSize;
	const int height = sceneContext.GameContext->GameSettings.WindowResolutionH / blockSize
		- topBorder / blockSize
		- bottomBorder / blockSize;

	int index = 0;

	// TODO: Figure out a prettier way to do this ?
	for (int i = 0; i < height; ++i)
	{
		x = halfSize;
		for (int j = 0; j < width; ++j)
		{
			switch (levelVec.at(index))
			{
			case DigDugLevel::LevelSectionType::Empty:
				break;
			case DigDugLevel::LevelSectionType::Block:
				Level::LevelBlock::CreateLevelBlock(go = nullptr, blockSize);
				AddGameObject(go);
				go->SetPosition(x, y);
				break;
			case DigDugLevel::LevelSectionType::Rock:
				Level::Rock::CreateRock(go = nullptr, blockSize);
				AddGameObject(go);
				go->SetPosition(x, y);
				break;
			case DigDugLevel::LevelSectionType::DigDug:
				m_PlayerSpawn = glm::vec2(x, y);

				Characters::DigDug::CreateDigDugCharacter(m_pDigDug, this, true);
				AddGameObject(m_pDigDug);
				m_pDigDug->SetPosition(x, y);

				if (m_GameMode == GameMode::Coop)
				{
					Characters::DigDug::CreateDigDugCharacter(m_pDigDug2, this, false);
					AddGameObject(m_pDigDug2);
					m_pDigDug2->SetPosition(x, y);
				}
				break;
			case DigDugLevel::LevelSectionType::Pooka:
				break;
			case DigDugLevel::LevelSectionType::Fygar:
				if(!m_IsFygarSpawned)
					m_FygarSpawn = glm::vec2(x, y);
				Characters::Fygar::CreateFygarCharacter(go = nullptr, this, (m_GameMode == GameMode::Versus)
					&& !m_IsFygarSpawned);
				AddGameObject(go);
				go->SetPosition(x, y);
				m_IsFygarSpawned = true;
				break;
			default:
				break;
			}

			x += blockSize;

			++index;
		}
		y += blockSize;
	}

	Level::BottomLayer::CreateBottomLayer(go = nullptr, sceneContext, blockSize);
	AddGameObject(go);
	go->SetPosition(float(sceneContext.GameContext->GameSettings.WindowResolutionW * .5f),
		float(sceneContext.GameContext->GameSettings.WindowResolutionH - blockSize * .5f));
}

void DigDugLevel::Update(const dae::SceneContext &)
{
}

void DigDugLevel::OnCollisionEnter(const dae::Contact &contact, dae::GameObject* gameObject)
{
	// TODO: Predefine tags pls
	// TODO: Move this to DigDug states?
	if (gameObject->GetTag() != "Rock" && contact.Other->GetTag() == "LevelBlock")
	{
		RemoveGameObject(contact.Other);
	}
}

void DigDugLevel::OnCollisionStay(const dae::Contact &, dae::GameObject* )
{
}

void DigDugLevel::OnCollisionExit(const dae::Contact &, dae::GameObject* )
{
}

void DigDugLevel::OnNotify(const dae::Subject* entity, int , va_list args)
{
	// TODO: Predefine this
	if (entity->GetTag() == "Player1" || entity->GetTag() == "Player2")
	{
		dae::HealthStatus status = va_arg(args, dae::HealthStatus);
		dae::GameObject* gameObject = va_arg(args, dae::GameObject*);

		switch (status)
		{
		case dae::HealthStatus::LostLife:
			LogDebugC("LostLife");
			ResetPlayer(gameObject);
			break;
		case dae::HealthStatus::Dead:
			LogDebugC("Dead");
			if (m_IsOnePlayerDead || m_GameMode == GameMode::SinglePlayer)
			{
				GetSceneContext().GameContext->Scenes->SetActiveScene("GameOverScene");
				Reset();
			}
			m_IsOnePlayerDead = true;			
			break;
		default:
			break;
		}
	}
}

void DigDugLevel::ResetPlayer(dae::GameObject* gameObject)
{
	if(gameObject->GetTag() == "DigDug")
		gameObject->SetPosition(m_PlayerSpawn);
	else
		gameObject->SetPosition(m_FygarSpawn);

	gameObject->GetComponent<dae::FSMComponent>()->ChangeState<Characters::DigDugEx::States::IdleState>(GetSceneContext());
}
