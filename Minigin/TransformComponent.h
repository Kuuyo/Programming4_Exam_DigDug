#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

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

		const glm::vec2 GetPosition(Anchor anchor = Anchor::TopLeft) const;
		void SetPosition(float x, float y, Anchor anchor = Anchor::TopLeft);

		const glm::vec2 GetOrentation() const;
		void SetOrientation(const glm::vec2 &orientation);
		void SetOrientation(float x, float y);
		void SetOrientationX(float x);
		void SetOrientationY(float y);

		TransformComponent(const TransformComponent &) = delete;
		TransformComponent(TransformComponent &&) = delete;
		TransformComponent & operator= (const TransformComponent &) = delete;
		TransformComponent & operator= (const TransformComponent &&) = delete;

	protected:
		void Initialize(const GameContext &gameContext) override;
		void Update(const GameContext &gameContext) override;
		void LateUpdate(const GameContext &) override {}

		virtual ~TransformComponent();

	private:
		glm::vec2 m_Position;
		glm::vec2 m_Orientation;
	};
}