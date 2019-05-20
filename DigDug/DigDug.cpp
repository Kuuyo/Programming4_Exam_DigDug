#include "pch.h"
#include "DigDug.h"

#include <SceneManager.h>
#include <InputManager.h>

#include "DigDugLevel.h"

void DigDug::LoadGame(const dae::GameContext &gameContext) const
{
	gameContext.Input->AddInputMapping(
		dae::InputMapping("P1Horizontal"
			, SDL_SCANCODE_D, SDL_SCANCODE_A
			, dae::GamePadAxis::LeftStickHorizontalAnalog, 0));

	gameContext.Input->AddInputMapping(
		dae::InputMapping("P1Vertical"
			, SDL_SCANCODE_S, SDL_SCANCODE_W
			, dae::GamePadAxis::LeftStickVerticalAnalog, 0));

	gameContext.Input->AddInputMapping(
		dae::InputMapping("P2Horizontal"
			, SDL_SCANCODE_KP_6, SDL_SCANCODE_KP_4
			, dae::GamePadAxis::LeftStickHorizontalAnalog, 1));

	gameContext.Input->AddInputMapping(
		dae::InputMapping("P2Vertical"
			, SDL_SCANCODE_KP_5, SDL_SCANCODE_KP_8
			, dae::GamePadAxis::LeftStickVerticalAnalog, 1));

	gameContext.Scenes->AddScene(new DigDugLevel("Level1", DigDugLevel::GameMode::Coop));
}
