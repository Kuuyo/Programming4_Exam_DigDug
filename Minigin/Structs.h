#pragma once
#include <SDL.h>
#include <string>

namespace dae
{
	enum class Direction // TODO: Decide what to do with this
	{
		Up,
		Down,
		Left,
		Right
	};

	enum class KeyState
	{
		Default,
		Triggered,
		Held,
		Released
	};

	struct InputMapping
	{
		InputMapping()
			: Name("")
			, Key(SDL_SCANCODE_UNKNOWN)
			, Mods(SDL_Keymod())
			, State(KeyState::Default)
			, HasGamePadSupport(false)
		{}

		InputMapping(std::string&& name,
			const SDL_Scancode &key)
			: Name(std::move(name))
			, Key(key)
			, Mods(SDL_Keymod())
			, State(KeyState::Default)
			, HasGamePadSupport(false)
		{}

		InputMapping(std::string&& name,
			const unsigned short &gamePadButton)
			: Name(std::move(name))
			, Key(SDL_SCANCODE_UNKNOWN)
			, Mods(SDL_Keymod())
			, State(KeyState::Default)
			, HasGamePadSupport(true)
			, GamePadButton(gamePadButton)
		{}

		InputMapping(std::string&& name,
			const SDL_Scancode &key,
			const unsigned short &gamePadButton)
			: Name(std::move(name))
			, Key(key)
			, Mods(SDL_Keymod())
			, State(KeyState::Default)
			, HasGamePadSupport(true)
			, GamePadButton(gamePadButton)
		{}

		std::string Name;
		SDL_Scancode Key;
		SDL_Keymod Mods;
		KeyState State;
		bool HasGamePadSupport;
		unsigned short GamePadButton;
	};
}