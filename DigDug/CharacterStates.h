#pragma once
#include "FSMComponent.h"

namespace Characters
{
	namespace DigDug_States
	{
		class IdleState final : public dae::State
		{
		public:
			~IdleState();

		private:
			void Initialize(const dae::GameContext &gameContext) override;

			void OnEnter(const dae::GameContext &gameContext) override;
			void Update(const dae::GameContext &gameContext) override;
			void OnExit(const dae::GameContext &gameContext) override;
		};

		class MovingState final : public dae::State
		{
		public:
			~MovingState();

		private:
			void Initialize(const dae::GameContext &gameContext) override;

			void OnEnter(const dae::GameContext &gameContext) override;
			void Update(const dae::GameContext &gameContext) override;
			void OnExit(const dae::GameContext &gameContext) override;
		};
	}
}