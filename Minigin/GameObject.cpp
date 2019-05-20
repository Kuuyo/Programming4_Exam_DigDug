#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"
#include "BodyComponent.h"

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
	}

	void GameObject::Initialize(const SceneContext &sceneContext)
	{
		for (auto pComponent : m_pVecComponents)
		{
			pComponent->Initialize(sceneContext);
		}

		m_IsInitialized = true;
	}

	void GameObject::Update(const SceneContext &sceneContext)
	{
		for (auto pComponent : m_pVecComponents)
		{
			pComponent->Update(sceneContext);
		}
	}

	void GameObject::LateUpdate(const SceneContext &sceneContext)
	{
		for (auto pComponent : m_pVecComponents)
		{
			pComponent->LateUpdate(sceneContext);
		}
	}

	void GameObject::AddComponent(BaseComponent* component)
	{
		m_pVecComponents.push_back(component);
		// TODO: Is GameObject being friend with BaseComponent to set it's parent what I want to do? public SetParent()?
		component->m_pParent = this;
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