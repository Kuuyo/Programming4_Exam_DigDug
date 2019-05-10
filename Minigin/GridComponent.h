#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GridComponent final : public BaseComponent
	{
	public:
		GridComponent();
		virtual ~GridComponent();

		GridComponent(const GridComponent &) = delete;
		GridComponent(GridComponent &&) = delete;
		GridComponent & operator= (const GridComponent &) = delete;
		GridComponent & operator= (const GridComponent &&) = delete;

		void Initialize(const GameContext &gameContext) override;
		void Update(const GameContext &gameContext) override;

	private:

	};
}