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
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void OnExit(const dae::SceneContext &sceneContext) override;
			};

			class WigglingState final : public dae::State
			{
			public:
				~WigglingState();

			private:
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void OnExit(const dae::SceneContext &sceneContext) override;

				float m_Timer{};
				float m_Duration{ 1.f };
				float m_ShakeElapsed{};
				float m_ShakeOffset{ 1.f };
				int m_NumberOfShakes{ 4 };
				int m_CurrentAmountOfShakes{};
			};

			class FallingState final : public dae::State
			{
			public:
				~FallingState();

			private:
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void OnExit(const dae::SceneContext &sceneContext) override;
			};

			class BreakingState final : public dae::State
			{
			public:
				~BreakingState();

			private:
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void OnExit(const dae::SceneContext &sceneContext) override;
			};
		}
	}
}