#pragma once

struct SDL_Window;

namespace dae
{
	class Log;

	class Minigin
	{
	public:
		void Run();

	protected:
		virtual void LoadGame() const = 0;

	private:
		void Initialize();
		void InitializeSDL();

		void GameLoop();

		void Cleanup();

		const unsigned int m_ConstFPS = 60;
		const float m_MsPerFrame = m_ConstFPS / 1000.f;
		const unsigned int m_MaxUpdates = 10;
		SDL_Window* m_pWindow{};
		Log* m_pLog{};
	};
}