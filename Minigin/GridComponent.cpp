#include "MiniginPCH.h"
#include "GridComponent.h"

#include "GameObject.h"
#include "BodyComponent.h"

#include <glm/detail/func_common.hpp>

namespace dae
{
	GridComponent::GridComponent(const float sectionSize, bool constrain)
		: m_SectionSize(sectionSize)
		, m_bConstrain(constrain)
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
		if (m_bConstrain && glm::abs(glm::distance(GetClosestGridPoint(), m_pParent->GetPosition())) < .001f)
		{
			auto pos = m_pParent->GetPosition();
			auto correction = GetClosestGridPoint() - pos;
			auto newPos = pos + correction;

			m_pParent->SetPosition(newPos);
		}
	}

	glm::vec2 GridComponent::GetClosestGridPointConstrained(Direction direction) const
	{
		glm::vec2 x, y, z;

		const auto pos = m_pParent->GetPosition();

		//if(glm::abs(glm::distance(pos, GetClosestGridPoint())) < .001f)
		//	return GetClosestGridPoint(direction);

		if(glm::abs(glm::distance(pos, GetClosestGridPoint(direction))) - .0015f <= 8.f)
			return GetClosestGridPoint(direction);

		switch (direction)
		{
		case dae::Direction::Up:
			x = GetClosestGridPoint(direction);
			y = GetClosestGridPoint(Direction::Left);
			z = GetClosestGridPoint(Direction::Right);
			break;
		case dae::Direction::Down:
			x = GetClosestGridPoint(direction);
			y = GetClosestGridPoint(Direction::Left);
			z = GetClosestGridPoint(Direction::Right);
			break;
		case dae::Direction::Left:
			x = GetClosestGridPoint(direction);
			y = GetClosestGridPoint(Direction::Up);
			z = GetClosestGridPoint(Direction::Down);
			break;
		case dae::Direction::Right:
			x = GetClosestGridPoint(direction);
			y = GetClosestGridPoint(Direction::Up);
			z = GetClosestGridPoint(Direction::Down);
			break;
		default:
			break;
		}


		std::map<float, glm::vec2> map{};

		const float xDist = glm::distance(pos, x);
		const float yDist = glm::distance(pos, y);
		const float zDist = glm::distance(pos, z);

		LogFormatC(dae::LogLevel::Debug, "x:%f y:%f z:%f", xDist, yDist, zDist);

		map.insert({ xDist,x });
		map.insert({ yDist,y });
		map.insert({ zDist,z });

		return map.at(glm::min(xDist, glm::min(yDist, zDist)));
	}

	glm::vec2 GridComponent::GetClosestGridPoint(float x, float y, Direction direction) const
	{
		switch (direction)
		{
		case dae::Direction::Up:
			return glm::vec2(m_SectionSize * (glm::round)(x / m_SectionSize), m_SectionSize * (glm::ceil)(y / m_SectionSize));
			break;
		case dae::Direction::Down:
			return glm::vec2(m_SectionSize * (glm::round)(x / m_SectionSize), m_SectionSize * (glm::floor)(y / m_SectionSize));
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
		switch (direction)
		{
		case dae::Direction::Up:
			pos.y += .1f;
			break;
		case dae::Direction::Down:
			pos.y -= .1f;
			break;
		case dae::Direction::Left:
			pos.x -= .1f;
			break;
		case dae::Direction::Right:
			pos.x += .1f;
			break;
		default:
			break;
		}
		return GetClosestGridPoint(pos.x, pos.y, direction);
	}

	glm::vec2 GridComponent::GetClosestGridPoint() const
	{
		const auto pos = m_pParent->GetPosition();
		return glm::vec2(m_SectionSize * (glm::floor)(pos.x / m_SectionSize), m_SectionSize * (glm::floor)(pos.y / m_SectionSize));
	}
}
