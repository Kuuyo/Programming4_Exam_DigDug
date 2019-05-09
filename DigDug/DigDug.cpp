#include "pch.h"
#include "DigDug.h"

#include "SceneManager.h"
#include "Level_1.h"

void DigDug::LoadGame(dae::GameContext gameContext) const
{
	gameContext.Scenes->AddScene(new Level_1());
}
