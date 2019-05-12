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

		virtual void Initialize(const GameContext &gameContext) = 0;

		virtual void OnEnter(const GameContext &gameContext) = 0;
		virtual void Update(const GameContext &gameContext) = 0;
		virtual void OnExit(const GameContext &gameContext) = 0;

		template <class T>
		void ChangeState()
		{
			m_pFSM->ChangeState<T>(*m_pGameContext);
		}

		GameObject* GetGameObject();

	private:
		friend FSMComponent;

		void RootInitialize(const GameContext &gameContext, FSMComponent* pParentFSM);

		FSMComponent* m_pFSM{ nullptr };
		InputManager* m_pInput{ nullptr };
		const GameContext* m_pGameContext{ nullptr };
	};

	class FSMComponent final : public BaseComponent
	{
	public:
		FSMComponent();
		virtual ~FSMComponent();

		FSMComponent(const FSMComponent&) = delete;
		FSMComponent(FSMComponent&&) = delete;
		FSMComponent &operator= (const FSMComponent&) = delete;
		FSMComponent &operator= (const FSMComponent&&) = delete;

		void Initialize(const GameContext &gameContext) override;
		void Update(const GameContext &gameContext) override;

		void AddState(State* pState);
		void RemoveState(State* pState);

		template <class T>
		void ChangeState(const GameContext &gameContext)
		{
			const type_info& ti = typeid(T);
			for (auto state : m_pStateMap)
			{
				if (state.first && typeid(*state.first) == ti)
				{
					m_pActiveState->OnExit(gameContext);

					m_pActiveState = state.first;

					m_pActiveState->OnEnter(gameContext);

					return;
				}
			}

			LogErrorC(std::string("Failed to find a matching State in the StateMap: ")
				+ std::string(ti.name()));
		}

	private:
		std::map<State*, bool> m_pStateMap{};
		State* m_pActiveState{ nullptr };
	};
}