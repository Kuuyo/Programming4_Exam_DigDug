#include "MiniginPCH.h"

#include "SceneManager.h"
#include "Scene.h"
#include "Renderer.h"
#include "GameContext.h"

dae::SceneManager::~SceneManager()
{
	for (auto scene : m_pScenesMap)
	{
		delete scene.second;
	} 
}

void dae::SceneManager::Initialize(const GameContext &gameContext)
{
	for (auto scene : m_pScenesMap)
	{
		scene.second->Initialize(gameContext);
	}
}

void dae::SceneManager::Update(const GameContext &gameContext)
{
	m_pActiveScene->Update(gameContext);
}

void dae::SceneManager::Render(const GameContext &gameContext, float extrapolate)
{
	m_pActiveScene->Render(gameContext.Renderer, extrapolate);
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
