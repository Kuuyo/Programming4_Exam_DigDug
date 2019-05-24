#pragma once
#include <FSMComponent.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	class BodyComponent;
	class TextureComponent;
}

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
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void OnExit(const dae::SceneContext &sceneContext) override;
			};

			class IdleState final : public dae::State
			{
			public:
				IdleState(std::string &&hAxis, std::string &&vAxis);
				~IdleState();

			private:
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void OnExit(const dae::SceneContext &sceneContext) override;

				std::string m_HAxis, m_VAxis;
			};

			class MovingState final : public dae::State
			{
			public:
				MovingState(std::string &&hAxis, std::string &&vAxis);
				~MovingState();

			private:
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void OnExit(const dae::SceneContext &sceneContext) override;

				std::string m_HAxis, m_VAxis;
			};

			class ThrowPumpState final : public dae::State
			{
			public:
				ThrowPumpState(std::string &&pumpMapping);
				~ThrowPumpState() = default;

				std::string GetPumpMapping() const { return m_PumpMapping; }

			private:
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void OnExit(const dae::SceneContext &sceneContext) override;

				std::string m_PumpMapping;
				dae::BodyComponent* m_pBody{ nullptr };
				dae::TextureComponent* m_pTexture{ nullptr };
				dae::GameObject* m_pPump{ nullptr };
				glm::vec2 m_OriginalLocalPos{};
				float m_HalfWidth;
			};

			class DeathState final : public dae::State
			{
			public:
				~DeathState() = default;

			private:
				void Initialize(const dae::SceneContext &sceneContext) override;

				void OnEnter(const dae::SceneContext &sceneContext) override;
				void Update(const dae::SceneContext &sceneContext) override;
				void OnExit(const dae::SceneContext &sceneContext) override;

				float m_Timer{};
				float m_Duration{ .5f };
			};
		}
	}
}