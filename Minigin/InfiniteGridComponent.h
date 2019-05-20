#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace dae
{
	class InfiniteGridComponent final : public BaseComponent
	{
	public:
		InfiniteGridComponent(const float sectionSize, bool constrain);

		InfiniteGridComponent(const InfiniteGridComponent &) = delete;
		InfiniteGridComponent(InfiniteGridComponent &&) = delete;
		InfiniteGridComponent & operator= (const InfiniteGridComponent &) = delete;
		InfiniteGridComponent & operator= (const InfiniteGridComponent &&) = delete;

		glm::vec2 GetClosestGridPointConstrained(Direction direction) const;
		glm::vec2 GetClosestGridPoint(float x, float y, Direction direction) const;
		glm::vec2 GetClosestGridPoint(Direction direction) const;
		glm::vec2 GetClosestGridPoint() const;

	protected:
		void Initialize(const SceneContext &sceneContext) override;
		void Update(const SceneContext &) override {}
		void LateUpdate(const SceneContext &sceneContext) override;

		virtual ~InfiniteGridComponent();

	private:
		const float m_SectionSize;
		bool m_bConstrain;
	};
}