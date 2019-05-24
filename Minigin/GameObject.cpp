#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComponent.h"
#include "BodyComponent.h"
#include "HelperFunctions.h"
#include "Scene.h"

namespace dae
{
	GameObject::GameObject()
		: GameObject("")
	{
	}

	GameObject::GameObject(std::string &&tag)
		: m_Tag(std::move(tag))
		, m_Position(0.f, 0.f)
		, m_LocalPosition(0.f, 0.f)
		, m_Orientation(1.f,1.f)
	{
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
		child->m_pParent = this;
	}

	void GameObject::RemoveChild(GameObject* child)
	{
		if (EraseRemoveFromVector(m_pChildren, child))
		{
			child->m_pScene = nullptr;
			child->m_pParent = nullptr;
		}
	}

	Scene* GameObject::GetScene() const
	{
		return m_pScene;
	}

	void GameObject::SetScene(Scene* pScene)
	{
		m_pScene = pScene;
	}

#pragma region Transform
	glm::vec2 GameObject::GetPosition(Anchor anchor) const
	{
		glm::vec2 newPos{ m_Position };

		auto gC = GetScene()->GetSceneContext().GameContext;

		// TODO: Fix this, it's garbage
		switch (anchor)
		{
		case Anchor::TopLeft:
			break;
		case Anchor::TopRight:
			newPos.x = gC->GameSettings.WindowResolutionW - newPos.x;
			break;
		case Anchor::BottomLeft:
			newPos.y = gC->GameSettings.WindowResolutionH - newPos.y;
			break;
		case Anchor::BottomRight:
			newPos.x = gC->GameSettings.WindowResolutionW - newPos.x;
			newPos.y = gC->GameSettings.WindowResolutionH - newPos.y;
			break;
		case Anchor::TopCenter:
			newPos.x = gC->GameSettings.WindowResolutionW * .5f + newPos.x;
			break;
		case Anchor::BottomCenter:
			newPos.x = gC->GameSettings.WindowResolutionW * .5f + newPos.x;
			newPos.y = gC->GameSettings.WindowResolutionH - newPos.y;
			break;
		case Anchor::Center:
			newPos.x = gC->GameSettings.WindowResolutionW * .5f + newPos.x;
			newPos.y = gC->GameSettings.WindowResolutionH * .5f + newPos.y;
			break;
		default:
			break;
		}

		return newPos;
	}

	void GameObject::SetPosition(float x, float y, Anchor anchor)
	{
		SetPosition(glm::vec2(x, y), anchor);
	}

	void GameObject::SetPosition(const glm::vec2 &newPos, Anchor anchor)
	{
		auto gC = GetScene()->GetSceneContext().GameContext;

		glm::vec2 tempNewPos{ newPos };

		// TODO: Fix this, it's garbage
		switch (anchor)
		{
		case Anchor::TopLeft:
			break;
		case Anchor::TopRight:
			tempNewPos.x = gC->GameSettings.WindowResolutionW - newPos.x;
			break;
		case Anchor::BottomLeft:
			tempNewPos.y = gC->GameSettings.WindowResolutionH - newPos.y;
			break;
		case Anchor::BottomRight:
			tempNewPos.x = gC->GameSettings.WindowResolutionW - newPos.x;
			tempNewPos.y = gC->GameSettings.WindowResolutionH - newPos.y;
			break;
		case Anchor::TopCenter:
			tempNewPos.x = gC->GameSettings.WindowResolutionW * .5f + newPos.x;
			break;
		case Anchor::BottomCenter:
			tempNewPos.x = gC->GameSettings.WindowResolutionW * .5f + newPos.x;
			tempNewPos.y = gC->GameSettings.WindowResolutionH - newPos.y;
			break;
		case Anchor::Center:
			tempNewPos.x = gC->GameSettings.WindowResolutionW * .5f + newPos.x;
			tempNewPos.y = gC->GameSettings.WindowResolutionH * .5f + newPos.y;
			break;
		default:
			break;
		}

		m_Position = tempNewPos;

		auto body = GetComponentNoError<BodyComponent>();

		if (body != nullptr && m_IsInitialized) // TODO: Bool for components to check if initialized ?
			body->SetPosition(m_Position);
	}

	glm::vec2 GameObject::GetLocalPosition() const
	{
		return m_LocalPosition;
	}

	void GameObject::SetLocalPosition(float x, float y)
	{
		SetLocalPosition(glm::vec2(x, y));
	}

	void GameObject::SetLocalPosition(const glm::vec2 &lPos)
	{
		m_LocalPosition = lPos;
	}

	glm::vec2 GameObject::GetOrentation() const
	{
		return m_Orientation;
	}

	void GameObject::SetOrientation(const glm::vec2 &orientation)
	{
		SetOrientationX(orientation.x);
		SetOrientationY(orientation.y);
	}

	void GameObject::SetOrientation(float x, float y)
	{
		SetOrientation(glm::vec2(x, y));
	}

	void GameObject::SetOrientationX(float x)
	{
		if (x != 0.f)
			m_Orientation.x = x > 0 ? 1.f : -1.f;
	}

	void GameObject::SetOrientationY(float y)
	{
		if (y != 0.f)
			m_Orientation.y = y > 0 ? 1.f : -1.f;
	}

	void GameObject::TransformUpdate()
	{
		if (m_pParent != nullptr)
		{
			m_Position = m_pParent->GetPosition() + m_LocalPosition;
		}
		else
		{
			m_LocalPosition = m_Position;
		}

		for (auto pChild : m_pChildren)
		{
			pChild->TransformUpdate();
		}
	}
#pragma endregion
}