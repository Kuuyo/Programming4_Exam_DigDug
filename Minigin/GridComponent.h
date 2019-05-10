#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace dae
{
	class GridComponent final : public BaseComponent
	{
	public:
		GridComponent(const float sectionSize);
		virtual ~GridComponent();

		GridComponent(const GridComponent &) = delete;
		GridComponent(GridComponent &&) = delete;
		GridComponent & operator= (const GridComponent &) = delete;
		GridComponent & operator= (const GridComponent &&) = delete;

		void Initialize(const GameContext &gameContext) override;
		void Update(const GameContext &gameContext) override;

		glm::vec2 GetClosestGridPoint(float x, float y, Direction direction) const;
		glm::vec2 GetClosestGridPoint(Direction direction) const;

	private:
		const float m_SectionSize;
	};
}