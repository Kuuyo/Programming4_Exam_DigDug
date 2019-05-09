#pragma once
#include "BaseComponent.h"

// TODO: Update TransformComponent to have more than just a SetPosition!

namespace dae
{
	enum class Anchor
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		TopCenter,
		BottomCenter,
		Center
	};

	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent();
		virtual ~TransformComponent();

		const glm::vec3 GetPosition(Anchor anchor = Anchor::TopLeft) const;
		void SetPosition(float x, float y, float z, Anchor anchor = Anchor::TopLeft);

		void Initialize(const GameContext &gameContext) override;
		void Update(const GameContext &gameContext) override;

		TransformComponent(const TransformComponent &) = delete;
		TransformComponent(TransformComponent &&) = delete;
		TransformComponent & operator= (const TransformComponent &) = delete;
		TransformComponent & operator= (const TransformComponent &&) = delete;

	private:
		glm::vec3 m_Position;
	};
}