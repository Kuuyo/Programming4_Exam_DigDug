#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Initialize()
{
	for (auto component : m_pVecComponents)
	{
		component->Initialize();
	}
}

void dae::GameObject::Update()
{
	for (auto component : m_pVecComponents)
	{
		component->Initialize();
	}
}

void dae::GameObject::Render() const
{
	for (auto component : m_pVecComponents)
	{
		component->Initialize();
	}
	const auto pos = mTransform.GetPosition();
	Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	m_pVecComponents.push_back(component);
	component->m_pParent = this;
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	mTransform.SetPosition(x, y, 0.0f);
}
