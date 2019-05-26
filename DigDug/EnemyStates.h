#pragma once
#include <FSMComponent.h>

namespace Characters
{
	namespace EnemyEx
	{
		namespace States
		{
			class GlobalState final : public dae::State
			{
			public:
				~GlobalState() = default;
	
			private:
				void Initialize(const dae::SceneContext &sceneContext) override;
	
				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void LateUpdate(const dae::SceneContext &) override {}
				void OnExit(const dae::SceneContext &sceneContext, State* pNextState) override;
			};
	
			class MovingState final : public dae::State
			{
			public:
				MovingState();
				~MovingState();
	
			private:
				void Initialize(const dae::SceneContext &sceneContext) override;
	
				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void LateUpdate(const dae::SceneContext &) override {}
				void OnExit(const dae::SceneContext &sceneContext, State* pNextState) override;

				float m_Horizontal, m_Vertical, m_Timer;
				float m_MaxInterval;
			};

			class GhostState final : public dae::State
			{
			public:
				~GhostState() = default;

			private:
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void LateUpdate(const dae::SceneContext &) override {}
				void OnExit(const dae::SceneContext &sceneContext, State* pNextState) override;

				float m_Timer{};
				float m_Duration{ .1f };
			};

			class HitState final : public dae::State
			{
			public:
				~HitState() = default;

			private:
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void LateUpdate(const dae::SceneContext &) override {}
				void OnExit(const dae::SceneContext &sceneContext, State* pNextState) override;
			};
	
			class DeathState final : public dae::State
			{
			public:
				~DeathState() = default;
	
			private:
				void Initialize(const dae::SceneContext &sceneContext) override;
	
				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void LateUpdate(const dae::SceneContext &) override {}
				void OnExit(const dae::SceneContext &sceneContext, State* pNextState) override;
	
				float m_Timer{};
				float m_Duration{ .1f };
			};
		}
	}
}