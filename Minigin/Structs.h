#pragma once
#include <SDL.h>
#include <string>

namespace dae
{
	struct InputMapping
	{
		std::string Name;
		SDL_Scancode Key;
		SDL_Keymod Mods;
		bool IsPressed;
		bool HasGamePadSupport;
		unsigned short GamePadButton;
	};
}