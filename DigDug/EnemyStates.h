#pragma once
#include <FSMComponent.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class EnemyComponent;

namespace dae
{
	class AnimatedSpriteComponent;
	class BodyComponent;
}

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
				MovingState(bool isFygar);
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

				float m_FireBreathTimer{}, m_RandomFireBreathInterval{};

				bool m_IsFygar{ false };
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
				dae::GameObject* m_pFollowedPlayer{ nullptr };
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

	namespace FygarEx
	{
		namespace States
		{
			class FireBreathingState final : public dae::State
			{
			public:
				~FireBreathingState() = default;

			private:
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void LateUpdate(const dae::SceneContext &) override {}
				void OnExit(const dae::SceneContext &sceneContext, State* pNextState) override;

				dae::BodyComponent* m_pBody{ nullptr };
				dae::AnimatedSpriteComponent* m_pTexture{ nullptr };
				dae::GameObject* m_pFire{ nullptr };
				glm::vec2 m_OriginalLocalPos{};
				float m_HalfWidth;
			};
		}
	}
}