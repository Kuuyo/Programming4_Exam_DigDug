#pragma once

struct SDL_Window;

namespace dae
{
	class Minigin
	{
		const float m_MsPerFrame = 0.01667f; //16 for 60 fps, 33 for 30 fps
		const unsigned int m_MaxUpdates = 10;
		SDL_Window* window{};
	public:
		void Run();

		void Initialize();
		void InitializeSDL();

		void LoadGame() const;
		void GameLoop();

		void Cleanup();		
	};
}