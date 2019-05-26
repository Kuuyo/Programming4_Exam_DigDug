#include "pch.h"
#include "DigDug.h"

#include <SceneManager.h>
#include <InputManager.h>

#include "MainMenu.h"
#include "DigDugLevel.h"
#include "GameOverScene.h"
#include "Settings.h"

void DigDug::LoadGame(const dae::GameContext &gameContext) const
{
	gameContext.Input->AddInputMapping(
		dae::InputMapping(Settings::P1HAxis
			, SDL_SCANCODE_D, SDL_SCANCODE_A
			, dae::GamePadAxis::LeftStickHorizontalAnalog, 0));

	gameContext.Input->AddInputMapping(
		dae::InputMapping(Settings::P1VAxis
			, SDL_SCANCODE_S, SDL_SCANCODE_W
			, dae::GamePadAxis::LeftStickVerticalAnalog, 0));

	gameContext.Input->AddInputMapping(
		dae::InputMapping(Settings::P1Pump
			, SDL_SCANCODE_SPACE
			, XINPUT_GAMEPAD_A, 0));

	gameContext.Input->AddInputMapping(
		dae::InputMapping(Settings::P2HAxis
			, SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT
			, dae::GamePadAxis::LeftStickHorizontalAnalog, 1));

	gameContext.Input->AddInputMapping(
		dae::InputMapping(Settings::P2VAxis
			, SDL_SCANCODE_DOWN, SDL_SCANCODE_UP
			, dae::GamePadAxis::LeftStickVerticalAnalog, 1));

	gameContext.Input->AddInputMapping(
		dae::InputMapping(Settings::P2Pump
			, SDL_SCANCODE_RCTRL
			, XINPUT_GAMEPAD_A, 1));

	gameContext.Input->AddInputMapping(
		dae::InputMapping(Settings::Confirm
			, SDL_SCANCODE_RETURN
			, XINPUT_GAMEPAD_START, 0));

	gameContext.Scenes->AddScene(new MainMenu());

	gameContext.Scenes->AddScene(new DigDugLevel("Level1_SP", "Level1", DigDugLevel::GameMode::SinglePlayer));
	gameContext.Scenes->AddScene(new DigDugLevel("Level1_Coop", "Level1", DigDugLevel::GameMode::Coop));
	gameContext.Scenes->AddScene(new DigDugLevel("Level1_Versus", "Level1", DigDugLevel::GameMode::Versus));

	gameContext.Scenes->AddScene(new DigDugLevel("Level2_SP", "Level2", DigDugLevel::GameMode::SinglePlayer));
	gameContext.Scenes->AddScene(new DigDugLevel("Level2_Coop", "Level2", DigDugLevel::GameMode::Coop));
	gameContext.Scenes->AddScene(new DigDugLevel("Level2_Versus", "Level2", DigDugLevel::GameMode::Versus));

	gameContext.Scenes->AddScene(new GameOverScene());
}
