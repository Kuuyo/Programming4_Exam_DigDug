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
}

namespace dae
{
	FSMComponent::FSMComponent()
	{
	}

	FSMComponent::~FSMComponent()
	{
		RemoveGlobalState();

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

		if (m_pGlobalState != nullptr)
		{
			m_pGlobalState->RootInitialize(gameContext, this);
			m_pGlobalState->OnEnter(gameContext);
		}

		m_pActiveState->OnEnter(gameContext);
	}

	void FSMComponent::Update(const GameContext &gameContext)
	{
		if(m_pGlobalState != nullptr)
			m_pGlobalState->Update(gameContext);
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

	void FSMComponent::SetGlobalState(State* pState)
	{
		RemoveGlobalState();

		m_pGlobalState = pState;
	}

	void FSMComponent::RemoveGlobalState()
	{
		if (m_pGlobalState != nullptr)
		{
			m_pGlobalState->OnExit(*m_pGlobalState->m_pGameContext);
			delete m_pGlobalState;
			m_pGlobalState = nullptr;
		}
	}
}
