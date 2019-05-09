#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"


dae::TransformComponent::TransformComponent()
{
}


dae::TransformComponent::~TransformComponent()
{
}

const glm::vec3 dae::TransformComponent::GetPosition(Anchor anchor) const
{
	glm::vec3 newPos{ m_Position };

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

void dae::TransformComponent::SetPosition(float x, float y, float z, Anchor anchor)
{
	glm::vec3 newPos{ x,y,z };

	// TODO: Fix Scene not being accessible before after the GO is added to it
	LogInfoC(m_pParent->GetTag());
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

void dae::TransformComponent::Initialize(const GameContext &)
{
}

void dae::TransformComponent::Update(const GameContext &)
{
}
