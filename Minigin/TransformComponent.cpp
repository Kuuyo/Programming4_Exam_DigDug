#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"

namespace dae
{
	TransformComponent::TransformComponent()
	{
	}


	TransformComponent::~TransformComponent()
	{
	}

	const glm::vec2 TransformComponent::GetPosition(Anchor anchor) const
	{
		glm::vec2 newPos{ m_Position };

		// TODO: Fix Scene not being accessible before after the GO is added to it
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

		// TODO: Fix Scene not being accessible before after the GO is added to it
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

	void TransformComponent::Initialize(const GameContext &)
	{
	}

	void TransformComponent::Update(const GameContext &)
	{
	}
}