#pragma once
class b2World;

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
		b2World* Physics{ nullptr };
	};
}