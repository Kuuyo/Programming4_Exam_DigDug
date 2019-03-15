#pragma once

struct SDL_Window;

namespace dae
{
	class Minigin
	{
		const float msPerFrame = 0.01667f; //16 for 60 fps, 33 for 30 fps
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