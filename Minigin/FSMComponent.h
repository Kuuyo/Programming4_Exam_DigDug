#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <map>

namespace dae
{
	class FSMComponent;
	class InputManager;

	class State
	{
	public:
		State() = default;

		State(const State&) = delete;
		State(State&&) = delete;
		State &operator= (const State&) = delete;
		State &operator= (const State&&) = delete;

	protected:
		virtual ~State();

		virtual void Initialize(const SceneContext &sceneContext) = 0;

		virtual void OnEnter(const SceneContext &sceneContext) = 0;
		virtual void Update(const SceneContext &sceneContext) = 0;
		virtual void OnExit(const SceneContext &sceneContext) = 0;

		template <class T>
		bool IsActiveState();

		template <class T>
		void ChangeState()
		{
			m_pFSM->ChangeState<T>(*m_pSceneContext);
		}

		template <class T>
		T* GetState();

		GameObject* GetGameObject();

	private:
		friend FSMComponent;

		void RootInitialize(const SceneContext &sceneContext, FSMComponent* pParentFSM);

		FSMComponent* m_pFSM{ nullptr };
		InputManager* m_pInput{ nullptr };
		const SceneContext* m_pSceneContext{ nullptr };
	};

	class FSMComponent final : public BaseComponent
	{
	public:
		FSMComponent();

		FSMComponent(const FSMComponent&) = delete;
		FSMComponent(FSMComponent&&) = delete;
		FSMComponent &operator= (const FSMComponent&) = delete;
		FSMComponent &operator= (const FSMComponent&&) = delete;

		void AddState(State* pState);
		void RemoveState(State* pState);

		void SetGlobalState(State* pState);
		void RemoveGlobalState();

		template <class T>
		bool IsActiveState()
		{
			const type_info& ti = typeid(T);
			return typeid(*m_pActiveState) == ti;
		}

		template <class T>
		void ChangeState(const SceneContext &sceneContext)
		{
			const type_info& ti = typeid(T);
			for (auto state : m_pStateMap)
			{
				if (state.first && typeid(*state.first) == ti)
				{
					m_pActiveState->OnExit(sceneContext);

					m_pActiveState = state.first;

					m_pActiveState->OnEnter(sceneContext);

					return;
				}
			}

			LogErrorC(std::string("Failed to find a matching State in the StateMap: ")
				+ std::string(ti.name()));
		}

		template <class T>
		T* GetState()
		{
			const type_info& ti = typeid(T);
			for (auto state : m_pStateMap)
			{
				if (state.first && typeid(*state.first) == ti)
				{
					return static_cast<T*>(state.first);
				}
			}

			return nullptr;
		}

	protected:
		void Initialize(const SceneContext &sceneContext) override;
		void Update(const SceneContext &sceneContext) override;
		void LateUpdate(const SceneContext &) override {}

		virtual ~FSMComponent();

	private:
		std::map<State*, bool> m_pStateMap{};
		State* m_pActiveState{ nullptr };
		State* m_pGlobalState{ nullptr };
	};

	template<class T>
	inline bool State::IsActiveState()
	{
		return m_pFSM->IsActiveState<T>();
	}

	template<class T>
	inline T* State::GetState()
	{
		return m_pFSM->GetState<T>();
	}
}