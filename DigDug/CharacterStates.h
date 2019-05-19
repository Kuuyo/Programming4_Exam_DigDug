#pragma once
#include <FSMComponent.h>

namespace Characters
{
	namespace DigDugEx
	{
		namespace States
		{
			class GlobalState final : public dae::State
			{
			public:
				~GlobalState() = default;

			private:
				void Initialize(const dae::GameContext &gameContext) override;

				void OnEnter(const dae::GameContext &gameContext) override;
				void Update(const dae::GameContext &gameContext) override;
				void OnExit(const dae::GameContext &gameContext) override;
			};

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

			class DeathState final : public dae::State
			{
			public:
				~DeathState() = default;

			private:
				void Initialize(const dae::GameContext &gameContext) override;

				void OnEnter(const dae::GameContext &gameContext) override;
				void Update(const dae::GameContext &gameContext) override;
				void OnExit(const dae::GameContext &gameContext) override;
			};
		}
	}
}