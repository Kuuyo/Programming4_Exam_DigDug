#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace dae
{
	class GridComponent final : public BaseComponent
	{
	public:
		GridComponent(const float sectionSize, bool constrain);

		GridComponent(const GridComponent &) = delete;
		GridComponent(GridComponent &&) = delete;
		GridComponent & operator= (const GridComponent &) = delete;
		GridComponent & operator= (const GridComponent &&) = delete;

		glm::vec2 GetClosestGridPointConstrained(Direction direction) const;
		glm::vec2 GetClosestGridPoint(float x, float y, Direction direction) const;
		glm::vec2 GetClosestGridPoint(Direction direction) const;
		glm::vec2 GetClosestGridPoint() const;

	protected:
		void Initialize(const GameContext &gameContext) override;
		void Update(const GameContext &gameContext) override;
		void LateUpdate(const GameContext &) override {}

		virtual ~GridComponent();

	private:
		const float m_SectionSize;
		bool m_bConstrain;
	};
}