#pragma once
#include <FSMComponent.h>

class EnemyComponent;

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

				float m_Horizontal, m_Vertical;
				float m_Timer{}, m_RandomInterval{};

				float m_GhostTimer{}, m_RandomGhostInterval{};
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

				EnemyComponent* m_pEnemyComponent{ nullptr };
				float m_Timer, m_MinGhostTime{ .3f };
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