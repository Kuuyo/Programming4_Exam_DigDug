#pragma once
class b2World;

namespace dae
{
	class SceneManager;
	class InputManager;
	class Renderer;
	class ResourceManager;
	class Time;

	struct GameSettings
	{
		GameSettings()
			: WindowTitle("Minigin")
			, WindowResolutionW(640)
			, WindowResolutionH(480)
			, GameScaleX(1.f)
			, GameScaleY(1.f)
		{}

		GameSettings(std::string &&windowTitle,
			int windowResolutionW,
			int windowResolutionH,
			float gameScaleX,
			float gameScaleY)
			: WindowTitle(std::move(windowTitle))
			, WindowResolutionW(windowResolutionW)
			, WindowResolutionH(windowResolutionH)
			, GameScaleX(gameScaleX)
			, GameScaleY(gameScaleY)
			, WindowWidth(int(windowResolutionW * gameScaleX))
			, WindowHeight(int(windowResolutionH * gameScaleY))
		{}

		std::string WindowTitle;
		int WindowResolutionW;
		int WindowResolutionH;
		int WindowWidth;
		int WindowHeight;
		float GameScaleX;
		float GameScaleY;
	};

	struct GameContext
	{
		GameSettings GameSettings{};
		SceneManager* Scenes{ nullptr };
		InputManager* Input{ nullptr };
		Renderer* Renderer{ nullptr };
		ResourceManager* Resources{ nullptr };
		Time* Time{ nullptr };
	};

	struct SceneContext // TODO: Finish SceneContext
	{
		const GameContext* GameContext;
		b2World* Physics{ nullptr };
		// Time
	};
}