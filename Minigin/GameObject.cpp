#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"
#include "BodyComponent.h"
#include "HelperFunctions.h"

namespace dae
{

	GameObject::GameObject()
	{
		m_pTransform = new TransformComponent();
		AddComponent(m_pTransform);
	}

	GameObject::GameObject(std::string &&tag)
		: m_Tag(std::move(tag))
	{
		m_pTransform = new TransformComponent();
		AddComponent(m_pTransform);
	}

	GameObject::~GameObject()
	{
		for (auto pComponent : m_pVecComponents)
		{
			if (pComponent != nullptr)
				delete pComponent;
		}

		for (auto pChild : m_pChildren)
		{
			if (pChild != nullptr)
				delete pChild;
		}
	}

	void GameObject::Initialize(const SceneContext &sceneContext)
	{
		for (auto pComponent : m_pVecComponents)
		{
			pComponent->Initialize(sceneContext);
		}

		m_IsInitialized = true;

		for (auto pChild : m_pChildren)
		{
			pChild->Initialize(sceneContext);
		}
	}

	void GameObject::Update(const SceneContext &sceneContext)
	{
		for (auto pComponent : m_pVecComponents)
		{
			pComponent->Update(sceneContext);
		}

		for (auto pChild : m_pChildren)
		{
			pChild->Update(sceneContext);
		}
	}

	void GameObject::LateUpdate(const SceneContext &sceneContext)
	{
		for (auto pComponent : m_pVecComponents)
		{
			pComponent->LateUpdate(sceneContext);
		}

		for (auto pChild : m_pChildren)
		{
			pChild->LateUpdate(sceneContext);
		}
	}

	void GameObject::AddComponent(BaseComponent* component)
	{
		m_pVecComponents.push_back(component);
		// TODO: Is GameObject being friend with BaseComponent to set it's parent what I want to do? public SetParent()?
		component->m_pParent = this;
	}

	void GameObject::RemoveComponent(BaseComponent* component)
	{
		EraseRemoveFromVector(m_pVecComponents, component);
	}

	void GameObject::AddChild(GameObject* child)
	{
		m_pChildren.push_back(child);
		child->m_pScene = m_pScene;
	}

	void GameObject::RemoveChild(GameObject* child)
	{
		EraseRemoveFromVector(m_pChildren, child);
	}

	void GameObject::SetPosition(float x, float y, Anchor anchor)
	{
		m_pTransform->SetPosition(x, y, anchor);

		auto body = GetComponentNoError<BodyComponent>();

		if (body != nullptr && m_IsInitialized) // TODO: Bool for components to check if initialized ?
			body->SetPosition(m_pTransform->GetPosition());
	}

	void GameObject::SetPosition(glm::vec2 pos)
	{
		SetPosition(pos.x, pos.y, Anchor::TopLeft);
	}

	const glm::vec2 GameObject::GetPosition() const
	{
		return m_pTransform->GetPosition();
	}

	Scene* GameObject::GetScene() const
	{
		return m_pScene;
	}

	void GameObject::SetScene(Scene* pScene)
	{
		m_pScene = pScene;
	}
}