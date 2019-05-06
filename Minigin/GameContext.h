#pragma once

namespace dae
{
	class SceneManager;
	class InputManager;
	class Renderer;
	class ResourceManager;
	class Time;

	struct GameContext
	{
		SceneManager* Scenes{ nullptr };
		InputManager* Input{ nullptr };
		Renderer* Renderer{ nullptr };
		ResourceManager* Resources{ nullptr };
		Time* Time{ nullptr };
	};
}