#include "MiniginPCH.h"
#include "GridComponent.h"

#include "GameObject.h"

#include <glm/detail/func_common.hpp>

namespace dae
{
	GridComponent::GridComponent(const float sectionSize)
		: m_SectionSize(sectionSize)
	{
	}

	GridComponent::~GridComponent()
	{
	}

	void GridComponent::Initialize(const GameContext &)
	{
	}

	void GridComponent::Update(const GameContext &)
	{
	}

	glm::vec2 GridComponent::GetClosestGridPoint(float x, float y, Direction direction) const
	{
		switch (direction)
		{
		case dae::Direction::Up:
			return glm::vec2(m_SectionSize * (glm::round)(x / m_SectionSize), m_SectionSize * (glm::floor)(y / m_SectionSize));
			break;
		case dae::Direction::Down:
			return glm::vec2(m_SectionSize * (glm::round)(x / m_SectionSize), m_SectionSize * (glm::ceil)(y / m_SectionSize));
			break;
		case dae::Direction::Left:
			return glm::vec2(m_SectionSize * (glm::floor)(x / m_SectionSize), m_SectionSize * (glm::round)(y / m_SectionSize));
			break;
		case dae::Direction::Right:
			return glm::vec2(m_SectionSize * (glm::ceil)(x / m_SectionSize), m_SectionSize * (glm::round)(y / m_SectionSize));
			break;
		default:
			break;
		}

		return glm::vec2();
	}
	glm::vec2 GridComponent::GetClosestGridPoint(Direction direction) const
	{
		auto pos = m_pParent->GetPosition();
		GetClosestGridPoint(pos.x, pos.y, direction);
	}
}
