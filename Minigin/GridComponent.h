#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GridComponent final : public BaseComponent
	{
	public:
		GridComponent(int sectionSize, const glm::vec2 &origin, int width, int height, bool snapToGrid);

		GridComponent(const GridComponent &) = delete;
		GridComponent(GridComponent &&) = delete;
		GridComponent & operator= (const GridComponent &) = delete;
		GridComponent & operator= (const GridComponent &&) = delete;

		std::vector<glm::vec2> GetClosestGridPoints(const glm::vec2 &position) const;
		glm::vec2 GetClosestGridPoint(const glm::vec2 &position) const;
		glm::vec2 GetNextGridPoint(const glm::vec2 &position, const glm::vec2 &direction) const;
		bool IsValidGridPoint(const glm::vec2 &point) const;
		bool IsOnGrid(const glm::vec2 &point) const;
		std::vector<glm::vec2> GetGrid() const;

		glm::vec2 SnapToGrid(const glm::vec2 &pos) const;

	protected:
		void Initialize(const SceneContext &sceneContext) override;
		void Update(const SceneContext &) override {}
		void LateUpdate(const SceneContext &sceneContext) override;

		virtual ~GridComponent();

	private:
		const int m_SectionSize;
		const glm::vec2 m_Origin;
		const int m_Width, m_Height, m_NrOfRows, m_NrOfColums;
		std::vector<glm::vec2> m_GridPointsVec;
		const bool m_SnapToGrid;
	};
}