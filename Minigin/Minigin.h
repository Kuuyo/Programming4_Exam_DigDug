#pragma once

struct SDL_Window;

namespace dae
{
	class Log;

	class Minigin
	{
		const unsigned int m_ConstFPS = 60;
		const float m_MsPerFrame = m_ConstFPS / 1000.f;
		const unsigned int m_MaxUpdates = 10;
		SDL_Window* m_pWindow{};
		Log* m_pLog{};

	public:
		void Run();

		void Initialize();
		void InitializeSDL();

		void LoadGame() const;
		void GameLoop();

		void Cleanup();		
	};
}