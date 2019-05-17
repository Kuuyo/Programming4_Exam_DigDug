#pragma once
#include <FSMComponent.h>

namespace Level
{
	namespace RockEx
	{
		namespace States
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

			class WigglingState final : public dae::State
			{
			public:
				~WigglingState();

			private:
				void Initialize(const dae::GameContext &gameContext) override;

				void OnEnter(const dae::GameContext &gameContext) override;
				void Update(const dae::GameContext &gameContext) override;
				void OnExit(const dae::GameContext &gameContext) override;

				float m_Timer{};
				float m_TimerMax{ 1.f };
			};

			class FallingState final : public dae::State
			{
			public:
				~FallingState();

			private:
				void Initialize(const dae::GameContext &gameContext) override;

				void OnEnter(const dae::GameContext &gameContext) override;
				void Update(const dae::GameContext &gameContext) override;
				void OnExit(const dae::GameContext &gameContext) override;
			};
		}
	}
}