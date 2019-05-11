#include "pch.h"
#include "DigDug.h"

#include "SceneManager.h"
#include "InputManager.h"

#include "Level_1.h"

void DigDug::LoadGame(const dae::GameContext &gameContext) const
{
	gameContext.Input->AddInputMapping(dae::InputMapping("Right", SDL_SCANCODE_D));

	gameContext.Scenes->AddScene(new Level_1());
}
