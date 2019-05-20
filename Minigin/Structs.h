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

	enum class GamePadAxis
	{
		None,
		LeftStickHorizontal,
		LeftStickVertical,
		RightStickHorizontal,
		RightStickVertical,
		LeftTrigger,
		RightTrigger,
		LeftStickHorizontalAnalog,
		LeftStickVerticalAnalog,
		RightStickHorizontalAnalog,
		RightStickVerticalAnalog,
	};

	struct InputMapping
	{
		InputMapping()
			: Name("")
			, PositiveKey(SDL_SCANCODE_UNKNOWN)
			, NegativeKey(SDL_SCANCODE_UNKNOWN)
			, Mods(SDL_Keymod())
			, State(KeyState::Default)
			, Axis(0.f)
			, HasGamePadButton(false)
			, HasGamePadAxis(false)
			, PlayerIndex(0)
			, GamePadAxis(GamePadAxis::None)
		{}

		InputMapping(std::string&& name,
			const SDL_Scancode &key)
			: Name(std::move(name))
			, PositiveKey(key)
			, NegativeKey(SDL_SCANCODE_UNKNOWN)
			, Mods(SDL_Keymod())
			, State(KeyState::Default)
			, Axis(0.f)
			, HasGamePadButton(false)
			, HasGamePadAxis(false)
			, PlayerIndex(0)
			, GamePadAxis(GamePadAxis::None)
		{}

		InputMapping(std::string&& name,
			const unsigned short &gamePadButton, unsigned int playerIndex)
			: Name(std::move(name))
			, PositiveKey(SDL_SCANCODE_UNKNOWN)
			, NegativeKey(SDL_SCANCODE_UNKNOWN)
			, Mods(SDL_Keymod())
			, State(KeyState::Default)
			, Axis(0.f)
			, HasGamePadButton(true)
			, HasGamePadAxis(false)
			, PlayerIndex(playerIndex)
			, GamePadButton(gamePadButton)
			, GamePadAxis(GamePadAxis::None)
		{}

		InputMapping(std::string&& name,
			const SDL_Scancode &key,
			const unsigned short &gamePadButton, unsigned int playerIndex)
			: Name(std::move(name))
			, PositiveKey(key)
			, NegativeKey(SDL_SCANCODE_UNKNOWN)
			, Mods(SDL_Keymod())
			, State(KeyState::Default)
			, Axis(0.f)
			, HasGamePadButton(true)
			, HasGamePadAxis(false)
			, PlayerIndex(playerIndex)
			, GamePadButton(gamePadButton)
			, GamePadAxis(GamePadAxis::None)
		{}

		InputMapping(std::string&& name,
			const SDL_Scancode &positiveKey,
			const SDL_Scancode &negativeKey )
			: Name(std::move(name))
			, PositiveKey(positiveKey)
			, NegativeKey(negativeKey)
			, Mods(SDL_Keymod())
			, State(KeyState::Default)
			, Axis(0.f)
			, HasGamePadButton(false)
			, HasGamePadAxis(false)
			, GamePadAxis(GamePadAxis::None)
		{}

		InputMapping(std::string&& name,
			const SDL_Scancode &positiveKey,
			const SDL_Scancode &negativeKey,
			const GamePadAxis gamePadAxis, unsigned int playerIndex)
			: Name(std::move(name))
			, PositiveKey(positiveKey)
			, NegativeKey(negativeKey)
			, Mods(SDL_Keymod())
			, State(KeyState::Default)
			, Axis(0.f)
			, HasGamePadButton(false)
			, HasGamePadAxis(true)
			, PlayerIndex(playerIndex)
			, GamePadAxis(gamePadAxis)
		{}

		std::string Name;
		bool HasGamePadButton;
		bool HasGamePadAxis;
		SDL_Scancode PositiveKey;
		SDL_Scancode NegativeKey;
		SDL_Keymod Mods;
		KeyState State;
		float Axis;
		unsigned int PlayerIndex;
		unsigned short GamePadButton;
		GamePadAxis GamePadAxis;
	};
}