#pragma once
#include "GameContext.h"

struct SDL_Window;

namespace dae
{
	class Log;

	class Minigin
	{
	public:
		void Run(const GameSettings &gameSettings);

	protected:
		virtual void LoadGame(const GameContext &gameContext) const = 0;

	private:
		void Initialize(const GameSettings &gameSettings);
		void InitializeSDL(const GameSettings &gameSettings);
		
		void GameLoop();

		void Cleanup();

		const unsigned int m_ConstFPS = 60;
		const float m_MsPerFrame = 1.f / m_ConstFPS;
		const unsigned int m_MaxUpdates = 10;
		SDL_Window* m_pWindow{};

		GameContext m_GameContext;
		GameSettings m_GameSettings;
	};
}