#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

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
	const auto pos = m_pTransform->GetPosition();
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	m_pVecComponents.push_back(component);
	component->m_pParent = this;
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_pTransform->SetPosition(x, y, 0.0f);
}

const glm::vec3& dae::GameObject::GetPosition() const
{
	return m_pTransform->GetPosition();
}