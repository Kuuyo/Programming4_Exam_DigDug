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

	void State::RootInitialize(const SceneContext &sceneContext, FSMComponent* pParentFSM)
	{
		m_pInput = sceneContext.GameContext->Input;

		m_pFSM = pParentFSM;
		m_pSceneContext = &sceneContext;

		Initialize(sceneContext);
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

	void FSMComponent::Initialize(const SceneContext &sceneContext)
	{
		for (auto it : m_pStateMap)
		{
			it.first->RootInitialize(sceneContext, this);
		}

		if (m_pGlobalState != nullptr)
		{
			m_pGlobalState->RootInitialize(sceneContext, this);
			m_pGlobalState->OnEnter(sceneContext);
		}

		m_pActiveState->OnEnter(sceneContext);
	}

	void FSMComponent::Update(const SceneContext &sceneContext)
	{
		if(m_pGlobalState != nullptr)
			m_pGlobalState->Update(sceneContext);
		m_pActiveState->Update(sceneContext);
	}

	void FSMComponent::LateUpdate(const SceneContext & sceneContext)
	{
		if (m_pGlobalState != nullptr)
			m_pGlobalState->LateUpdate(sceneContext);
		m_pActiveState->LateUpdate(sceneContext);
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
			m_pGlobalState->OnExit(*m_pGlobalState->m_pSceneContext, nullptr);
			delete m_pGlobalState;
			m_pGlobalState = nullptr;
		}
	}
}
