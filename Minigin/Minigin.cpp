#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include <Box2D/Box2D.h>
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

namespace dae
{
	void Minigin::Run(const GameSettings &gameSettings)
	{
		Initialize(gameSettings);

		LoadGame(m_GameContext);

		GameLoop();

		Cleanup();
	}

	void Minigin::Initialize(const GameSettings &gameSettings)
	{
		Log::GetInstance().Initialize();

		InitializeSDL(gameSettings);

		m_GameContext = GameContext();
		m_GameContext.GameSettings = gameSettings;
		m_GameContext.Time = new Time();
		Log::GetInstance().SetGlobalTime(m_GameContext.Time);
		m_GameContext.Scenes = new SceneManager();
		m_GameContext.Renderer = new Renderer(m_pWindow, m_GameContext);
		m_GameContext.Resources = new ResourceManager();
		// TODO: ResourceManager Init: Don't forget to change the resource path if needed
		m_GameContext.Resources->Init("Data/", m_GameContext.Renderer);
		m_GameContext.Input = new InputManager();
	}

	void Minigin::InitializeSDL(const GameSettings &gameSettings)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			LogErrorC(std::string("SDL_Init Error: ") + SDL_GetError());
		}

		// TODO: Creating SDL Window properties: change resolution at runtime?
		m_pWindow = SDL_CreateWindow(
			gameSettings.WindowTitle.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			int(gameSettings.WindowWidth),
			int(gameSettings.WindowHeight),
			SDL_WINDOW_OPENGL
		);

		if (m_pWindow == nullptr)
		{
			LogErrorC(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
		}

		LogInfoC("Window created!");
	}

	// References: http://gameprogrammingpatterns.com/game-loop.html
	// Another view of the same deal: https://bell0bytes.eu/the-game-loop/
	void Minigin::GameLoop()
	{
		m_GameContext.Scenes->Initialize(m_GameContext);

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
				sceneManager->FixedUpdate(m_MsPerFrame);
				accumulatedTime -= m_MsPerFrame;
				++nrLoops;
			}

			sceneManager->Update();
			sceneManager->LateUpdate();
			
			sceneManager->DestroyUpdate();

			sceneManager->TransformUpdate();

			sceneManager->Render(m_GameContext, accumulatedTime / m_MsPerFrame);
			// TODO: I REEEAAALLY don't like how the Render is locking the loop to framerate
			// As it creates behaviour I REEEAAALLY hated in Unity -> Input is also tied to FPS now
		}
	}

	void Minigin::Cleanup()
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
}