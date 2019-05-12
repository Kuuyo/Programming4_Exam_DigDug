#include "pch.h"
#include "DigDug.h"

#include "SceneManager.h"
#include "InputManager.h"

#include "Level_1.h"

void DigDug::LoadGame(const dae::GameContext &gameContext) const
{
	gameContext.Input->AddInputMapping(
		dae::InputMapping("P1Horizontal"
			, SDL_SCANCODE_D, SDL_SCANCODE_A
			, dae::GamePadAxis::LeftStickHorizontal));

	gameContext.Input->AddInputMapping(
		dae::InputMapping("P1Vertical"
			, SDL_SCANCODE_W, SDL_SCANCODE_S
			, dae::GamePadAxis::LeftStickVertical));

	gameContext.Scenes->AddScene(new Level_1());
}
