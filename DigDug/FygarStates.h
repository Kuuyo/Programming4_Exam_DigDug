#pragma once
#include <FSMComponent.h>
#include <random>

namespace Characters
{
	namespace FygarEx
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
				void OnExit(const dae::SceneContext &sceneContext, State* pNextState) override;

				float GetRandomFloat(float min, float max);

				std::random_device m_RandomDevice;
				std::mt19937 m_RandomEngine;

				float m_Horizontal, m_Vertical, m_Timer;
				float m_MaxInterval;
			};

			class HitState final : public dae::State
			{
			public:
				~HitState() = default;

			private:
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
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
				void OnExit(const dae::SceneContext &sceneContext, State* pNextState) override;
	
				float m_Timer{};
				float m_Duration{ .5f };
			};
		}
	}
}