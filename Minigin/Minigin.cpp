#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"

#include "GameObject.h"
#include "Scene.h"

#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

void dae::Minigin::Run()
{
	Initialize();

	LoadGame(m_GameContext);

	GameLoop();

	Cleanup();
}

void dae::Minigin::Initialize()
{
	Log::GetInstance().Initialize();

	InitializeSDL();

	m_GameContext = GameContext();
	m_GameContext.Scenes = new SceneManager();
	m_GameContext.Renderer = new Renderer(m_pWindow);
	m_GameContext.Resources = new ResourceManager();
	// TODO: ResourceManager Init: Don't forget to change the resource path if needed
	m_GameContext.Resources->Init("Data/", m_GameContext.Renderer);
	m_GameContext.Input = new InputManager();
	m_GameContext.Time = new Time();
}

void dae::Minigin::InitializeSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	// TODO: Creating SDL Window properties: enable setting a custom title and resolution; Custom struct for Game Settings ?; Game Settings class for Options menu?
	// TODO: Creating SDL Window properties: change resolution at runtime?
	m_pWindow = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);

	LogInfoC("Window created!");

	if (m_pWindow == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
}

// References: http://gameprogrammingpatterns.com/game-loop.html
// Another view of the same deal: https://bell0bytes.eu/the-game-loop/
void dae::Minigin::GameLoop()
{
	m_GameContext.Scenes->Initialize(m_GameContext);
	// TODO: Currently there are quite a lot of singletons.. Create a struct and use dependency injection instead?
	auto* sceneManager = m_GameContext.Scenes;
	auto* input = m_GameContext.Input;
	auto* time = m_GameContext.Time;

	float accumulatedTime{ 0.f };
	bool doContinue = true;
	while (doContinue)
	{
		time->Tick();
		time->CalculateFrameStats();

		doContinue = input->ProcessInput();

		accumulatedTime += time->GetDeltaTime();

		unsigned int nrLoops{ 0 };
		while (accumulatedTime >= m_MsPerFrame && nrLoops < m_MaxUpdates)
		{
			sceneManager->Update(m_GameContext);
			accumulatedTime -= m_MsPerFrame;
			++nrLoops;
		}

		sceneManager->Render(m_GameContext, accumulatedTime / m_MsPerFrame);
	}
}

void dae::Minigin::Cleanup()
{
	delete m_GameContext.Scenes;
	delete m_GameContext.Time;	
	delete m_GameContext.Renderer;
	delete m_GameContext.Resources;
	delete m_GameContext.Input;

	Log::GetInstance().CleanUp();

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}