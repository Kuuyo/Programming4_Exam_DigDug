#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"

dae::GameObject::GameObject()
{
	m_pTransform = new TransformComponent();
	AddComponent(m_pTransform);
}

dae::GameObject::GameObject(std::string &&tag)
	: m_Tag(std::move(tag))
{
	m_pTransform = new TransformComponent();
	AddComponent(m_pTransform);
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

void dae::GameObject::SetPosition(float x, float y, float z, Anchor anchor)
{
	m_pTransform->SetPosition(x, y, z, anchor);
}

void dae::GameObject::SetPosition(glm::vec3 pos)
{
	m_pTransform->SetPosition(pos.x, pos.y, pos.z);
}

const glm::vec3 dae::GameObject::GetPosition() const
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
