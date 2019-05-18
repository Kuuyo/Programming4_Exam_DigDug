#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"

namespace dae
{
	TransformComponent::TransformComponent()
		: m_Position(0.f, 0.f)
		, m_Orientation(1.f, 1.f)
	{
	}


	TransformComponent::~TransformComponent()
	{
	}

	const glm::vec2 TransformComponent::GetPosition(Anchor anchor) const
	{
		glm::vec2 newPos{ m_Position };

		auto gC = m_pParent->GetScene()->GetSceneContext().GameContext;

		// TODO: Fix this, it's garbage
		switch (anchor)
		{
		case dae::Anchor::TopLeft:
			break;
		case dae::Anchor::TopRight:
			newPos.x = gC.GameSettings.WindowResolutionW - newPos.x;
			break;
		case dae::Anchor::BottomLeft:
			newPos.y = gC.GameSettings.WindowResolutionH - newPos.y;
			break;
		case dae::Anchor::BottomRight:
			newPos.x = gC.GameSettings.WindowResolutionW - newPos.x;
			newPos.y = gC.GameSettings.WindowResolutionH - newPos.y;
			break;
		case dae::Anchor::TopCenter:
			newPos.x = gC.GameSettings.WindowResolutionW * .5f + newPos.x;
			break;
		case dae::Anchor::BottomCenter:
			newPos.x = gC.GameSettings.WindowResolutionW * .5f + newPos.x;
			newPos.y = gC.GameSettings.WindowResolutionH - newPos.y;
			break;
		case dae::Anchor::Center:
			newPos.x = gC.GameSettings.WindowResolutionW * .5f + newPos.x;
			newPos.y = gC.GameSettings.WindowResolutionH * .5f + newPos.y;
			break;
		default:
			break;
		}

		return newPos;
	}

	void TransformComponent::SetPosition(float x, float y, Anchor anchor)
	{
		glm::vec2 newPos{ x,y };

		auto gC = m_pParent->GetScene()->GetSceneContext().GameContext;

		// TODO: Fix this, it's garbage
		switch (anchor)
		{
		case dae::Anchor::TopLeft:
			break;
		case dae::Anchor::TopRight:
			newPos.x = gC.GameSettings.WindowResolutionW - newPos.x;
			break;
		case dae::Anchor::BottomLeft:
			newPos.y = gC.GameSettings.WindowResolutionH - newPos.y;
			break;
		case dae::Anchor::BottomRight:
			newPos.x = gC.GameSettings.WindowResolutionW - newPos.x;
			newPos.y = gC.GameSettings.WindowResolutionH - newPos.y;
			break;
		case dae::Anchor::TopCenter:
			newPos.x = gC.GameSettings.WindowResolutionW * .5f + newPos.x;
			break;
		case dae::Anchor::BottomCenter:
			newPos.x = gC.GameSettings.WindowResolutionW * .5f + newPos.x;
			newPos.y = gC.GameSettings.WindowResolutionH - newPos.y;
			break;
		case dae::Anchor::Center:
			newPos.x = gC.GameSettings.WindowResolutionW * .5f + newPos.x;
			newPos.y = gC.GameSettings.WindowResolutionH * .5f + newPos.y;
			break;
		default:
			break;
		}

		m_Position = newPos;
	}

	const glm::vec2 TransformComponent::GetOrentation() const
	{
		return m_Orientation;
	}

	void TransformComponent::SetOrientation(const glm::vec2 &orientation)
	{
		SetOrientationX(orientation.x);
		SetOrientationY(orientation.y);
	}

	void TransformComponent::SetOrientation(float x, float y)
	{
		SetOrientation(glm::vec2(x, y));
	}

	void TransformComponent::SetOrientationX(float x)
	{
		if(x != 0.f)
			m_Orientation.x = x > 0 ? 1.f : -1.f;
	}

	void TransformComponent::SetOrientationY(float y)
	{
		if (y != 0.f)
			m_Orientation.y = y > 0 ? 1.f : -1.f;
	}

	void TransformComponent::Initialize(const GameContext &)
	{
	}

	void TransformComponent::Update(const GameContext &)
	{
	}
}