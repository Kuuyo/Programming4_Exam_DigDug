#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "Time.h"

#include "GameObject.h"
#include "Scene.h"

#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

void dae::Minigin::Run()
{
	Initialize();

	LoadGame();

	GameLoop();

	Cleanup();
}

void dae::Minigin::Initialize()
{
	InitializeSDL();

	Renderer::GetInstance().Init(window);
	// TODO: ResourceManager Init: Don't forget to change the resource path if needed
	ResourceManager::GetInstance().Init("../Data/");
}

void dae::Minigin::InitializeSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	// TODO: Creating SDL Window properties: enable setting a custom title and resolution; Custom struct for Game Settings ?; Game Settings class for Options menu?
	// TODO: Creating SDL Window properties: change resolution at runtime?
	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
}

// TODO: LoadGame: Create the actual game project and load scenes in there
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TextureComponent("background.jpg"));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new TextureComponent("logo.png"));
	go->SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new TextComponent("Programming 4 Assignment"));
	go->SetPosition(80, 20);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new FPSComponent());
	go->SetPosition(3, 3);
	scene.Add(go);
}

// References: http://gameprogrammingpatterns.com/game-loop.html
// Another view of the same deal: https://bell0bytes.eu/the-game-loop/
void dae::Minigin::GameLoop()
{
	// TODO: Currently there are quite a lot of singletons.. Create a struct and use dependency injection instead?
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = Time::GetInstance();

	sceneManager.Initialize();
	time.Initialize();

	float accumulatedTime{ 0.f };
	bool doContinue = true;
	while (doContinue)
	{
		time.Tick();
		time.CalculateFrameStats();

		doContinue = input.ProcessInput();

		accumulatedTime += time.GetDeltaTime();

		unsigned int nrLoops{ 0 };
		while (accumulatedTime >= m_MsPerFrame && nrLoops < m_MaxUpdates)
		{
			sceneManager.Update();
			accumulatedTime -= m_MsPerFrame;
			++nrLoops;
		}

		renderer.Render(accumulatedTime / m_MsPerFrame);
	}
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}