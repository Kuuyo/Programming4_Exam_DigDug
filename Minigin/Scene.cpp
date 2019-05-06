#include "MiniginPCH.h"
#include "Scene.h"

#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : m_Name(name) {}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

const std::string dae::Scene::GetName()
{
	return m_Name;
}

void dae::Scene::Initialize()
{
	for (auto gameObject : m_Objects)
	{
		gameObject->Initialize();
	}
}

void dae::Scene::Update()
{
	for(auto gameObject : m_Objects)
	{
		gameObject->Update();
	}
}

void dae::Scene::Render(float extrapolate) const
{
	(extrapolate); // TODO: Remember unreferenced parameter "extrapolate" in Scene::Render after deciding rendering of GameObject
	for (const auto gameObject : m_Objects)
	{
		gameObject->Render();
	}
}

