#pragma once
#include "BaseComponent.h"

namespace dae
{
	class MovementComponent final : public BaseComponent
	{
	public:
		MovementComponent();
		virtual ~MovementComponent();

		MovementComponent(const MovementComponent &) = delete;
		MovementComponent(MovementComponent &&) = delete;
		MovementComponent & operator= (const MovementComponent &) = delete;
		MovementComponent & operator= (const MovementComponent &&) = delete;

		void Initialize() override;
		void Update() override;
		void Render() override;

	private:
		UINT m_PlayerIndex;

	};
}