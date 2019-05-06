#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

// TODO: Currently the SceneManager updates and renders all scenes at once, remember to change this to only active scenes

void dae::SceneManager::Initialize()
{
	for (auto scene : m_pScenesMap)
	{
		scene.second->Initialize();
	}
}

void dae::SceneManager::Cleanup()
{
	for (auto scene : m_pScenesMap)
	{
		delete scene.second;
	}
}

void dae::SceneManager::Update()
{
	m_pActiveScene->Update();
}

void dae::SceneManager::Render(float extrapolate)
{
	m_pActiveScene->Render(extrapolate);
}

void dae::SceneManager::AddScene(Scene* pScene)
{
	m_pScenesMap.insert({ pScene->GetName(),pScene });
	if (m_pActiveScene == nullptr)
		m_pActiveScene = pScene;
}

void dae::SceneManager::RemoveScene(Scene* pScene)
{
	m_pScenesMap.erase(pScene->GetName());
}

void dae::SceneManager::RemoveScene(const std::string& sceneName)
{
	m_pScenesMap.erase(sceneName);
}

void dae::SceneManager::SetActiveScene(const std::string& sceneName)
{
	m_pActiveScene = m_pScenesMap.at(sceneName);
}

dae::Scene* dae::SceneManager::GetActiveScene() const
{
	return m_pActiveScene;
}
