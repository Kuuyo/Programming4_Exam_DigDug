#include "MiniginPCH.h"
#include "FSMComponent.h"

#include "InputManager.h"

namespace dae
{
	State::~State()
	{
	}

	GameObject* State::GetGameObject()
	{
		return m_pFSM->GetGameObject();
	}

	void State::RootInitialize(const GameContext &gameContext, FSMComponent* pParentFSM)
	{
		m_pInput = gameContext.Input;

		m_pFSM = pParentFSM;
		m_pGameContext = &gameContext;

		Initialize(gameContext);
	}

	void State::RootOnEnter(const GameContext &gameContext)
	{
		OnEnter(gameContext);
	}
	void State::RootOnExit(const GameContext &gameContext)
	{
		OnExit(gameContext);
	}
}

namespace dae
{
	FSMComponent::FSMComponent()
	{
	}

	FSMComponent::~FSMComponent()
	{
		for (auto it : m_pStateMap)
		{
			if(it.first != nullptr)
				delete it.first;
		}
	}

	void FSMComponent::Initialize(const GameContext &gameContext)
	{
		for (auto it : m_pStateMap)
		{
			it.first->RootInitialize(gameContext, this);
		}

		m_pActiveState->RootOnEnter(gameContext);
	}

	void FSMComponent::Update(const GameContext &gameContext)
	{
		m_pActiveState->Update(gameContext);
	}

	void FSMComponent::AddState(State* pState)
	{
		if (m_pActiveState == nullptr) // TODO: Use a starting state instead
			m_pActiveState = pState;

		m_pStateMap.insert({ pState, false });
	}

	void FSMComponent::RemoveState(State* pState)
	{
		m_pStateMap.erase(pState);
	}
}
