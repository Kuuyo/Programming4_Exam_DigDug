#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

// TODO: Currently the SceneManager updates and renders all scenes at once, remember to change this to only active scenes

void dae::SceneManager::Initialize()
{
	for (auto scene : mScenes)
	{
		scene->Initialize();
	}
}

void dae::SceneManager::Update()
{
	for(auto scene : mScenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto scene : mScenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	mScenes.push_back(scene);
	return *scene;
}
