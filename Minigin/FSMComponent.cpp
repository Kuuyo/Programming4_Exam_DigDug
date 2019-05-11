#include "MiniginPCH.h"
#include "FSMComponent.h"

#include "InputManager.h"

namespace dae
{
	State::~State()
	{
		m_pInput->RemoveObserver(this);
	}

	void State::RootInitialize(const GameContext &gameContext, FSMComponent* pParentFSM)
	{
		gameContext.Input->AddObserver(this);
		m_pInput = gameContext.Input;

		m_pFSM = pParentFSM;

		Initialize(gameContext);
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

		m_pActiveState->OnEnter(gameContext);
	}

	void FSMComponent::Update(const GameContext &gameContext)
	{
		m_pActiveState->Update(gameContext);
	}

	void FSMComponent::AddState(State* pState)
	{
		if (m_pActiveState == nullptr)
			m_pActiveState = pState;
		m_pStateMap.insert({ pState, false });
	}

	void FSMComponent::RemoveState(State* pState)
	{
		m_pStateMap.erase(pState);
	}
}
