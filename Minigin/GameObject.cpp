#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"
#include "TransformComponent.h"

dae::GameObject::GameObject()
{
	m_pTransform = new TransformComponent();
	m_pVecComponents.push_back(m_pTransform);
}

dae::GameObject::~GameObject()
{
	for (auto pComponent : m_pVecComponents)
	{
		delete pComponent;
	}
}

void dae::GameObject::Initialize(const GameContext &gameContext)
{
	for (auto pComponent : m_pVecComponents)
	{
		pComponent->Initialize(gameContext);
	}
}

void dae::GameObject::Update(const GameContext &gameContext)
{
	for (auto pComponent : m_pVecComponents)
	{
		pComponent->Update(gameContext);
	}
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	m_pVecComponents.push_back(component);
	// TODO: Is GameObject being friend with BaseComponent to set it's parent what I want to do? public SetParent()?
	component->m_pParent = this;
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	m_pTransform->SetPosition(x, y, z);
}

const glm::vec3& dae::GameObject::GetPosition() const
{
	return m_pTransform->GetPosition();
}

dae::Scene* dae::GameObject::GetScene() const
{
	return m_pScene;
}

void dae::GameObject::SetScene(Scene* pScene)
{
	m_pScene = pScene;
}
