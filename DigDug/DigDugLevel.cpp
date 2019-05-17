#include "pch.h"
#include "DigDugLevel.h"

#include <GameObject.h>
#include <TextureComponent.h>
#include <FPSComponent.h>
#include <ResourceManager.h>

#include <json.hpp>

#include "Prefabs.h"
#include "Characters.h"

DigDugLevel::DigDugLevel(std::string &&levelName)
	: Scene(levelName)
	, m_LevelName(std::move(levelName))
{
}


DigDugLevel::~DigDugLevel()
{
}

void DigDugLevel::Initialize(const dae::GameContext &gameContext)
{
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
	nlohmann::json jsonLevel = gameContext.Resources->LoadJson(m_LevelName + ".json");
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

	const int width = gameContext.GameSettings.WindowResolutionW / blockSize;
	const int height = gameContext.GameSettings.WindowResolutionH / blockSize
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
				Level::LevelBlock::CreateLevelBlock(go = new dae::GameObject("LevelBlock"), blockSize);
				AddGameObject(go);
				go->SetPosition(x, y);
				break;
			case DigDugLevel::LevelSectionType::Rock:
				Level::Rock::CreateRock(go = new dae::GameObject("Rock"), blockSize);
				AddGameObject(go);
				go->SetPosition(x, y);
				break;
			case DigDugLevel::LevelSectionType::DigDug:
				Characters::DigDug::CreateDigDugCharacter(m_pDigDug);
				AddGameObject(m_pDigDug);
				m_pDigDug->SetPosition(x, y);
				break;
			case DigDugLevel::LevelSectionType::Pooka:
				break;
			case DigDugLevel::LevelSectionType::Fygar:
				break;
			default:
				break;
			}

			x += blockSize;

			++index;
		}
		y += blockSize;
	}
}

void DigDugLevel::Update(const dae::GameContext &)
{
}

void DigDugLevel::OnCollisionEnter(const dae::Contact &contact, dae::GameObject* gameObject)
{
	// TODO: Predefine tags pls
	if (gameObject->GetTag() == "DigDug" && contact.Other->GetTag() == "LevelBlock")
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