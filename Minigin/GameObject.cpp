#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"
#include "TransformComponent.h"

// TODO: Right now all components are called to Update() and Render() -> Change this so they only Update() and rendering gets handled separately ?

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

void dae::GameObject::Initialize()
{
	for (auto pComponent : m_pVecComponents)
	{
		pComponent->Initialize();
	}
}

void dae::GameObject::Update()
{
	for (auto pComponent : m_pVecComponents)
	{
		pComponent->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto pComponent : m_pVecComponents)
	{
		pComponent->Render();
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