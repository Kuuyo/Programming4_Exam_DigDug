#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "Time.h"
#include "InputManager.h"
#include "BodyComponent.h"

dae::MovementComponent::MovementComponent(int playerIndex)
	:m_PlayerIndex(playerIndex)
{
	m_Direction.insert({ "Up",glm::vec3(0.f,-1.f,0.f) });
	m_Direction.insert({ "Down",glm::vec3(0.f,1.f,0.f) });
	m_Direction.insert({ "Left",glm::vec3(-1.f,0.f,0.f) });
	m_Direction.insert({ "Right",glm::vec3(1.f,0.f,0.f) });

	m_Speed = 100.f;
}


dae::MovementComponent::~MovementComponent()
{
	m_pInput->RemoveObserver(this);
}

void dae::MovementComponent::Initialize(const GameContext &gameContext)
{
	m_pInput = gameContext.Input;
	m_pInput->AddObserver(this);

	m_bHasBody = m_pParent->HasComponent<BodyComponent>();

	// TODO: Make Input in MovementComponent not hardcoded
	InputMapping im = InputMapping();
	im.Name = "Up";
	m_InputMappingMap.insert({ SDL_SCANCODE_W, im });
	im.Name = "Down";
	m_InputMappingMap.insert({ SDL_SCANCODE_S, im });
	im.Name = "Left";
	m_InputMappingMap.insert({ SDL_SCANCODE_A, im });
	im.Name = "Right";
	m_InputMappingMap.insert({ SDL_SCANCODE_D, im });
}

void dae::MovementComponent::Update(const GameContext &gameContext)
{
	if (!m_bHasBody)
	{
		for (auto im : m_InputMappingMap)
			if (im.second.IsPressed)
				m_pParent->SetPosition(
					m_pParent->GetPosition() +
					(m_Direction.at(im.second.Name) * gameContext.Time->GetDeltaTime() * m_Speed)
				);
	}		
	else
	{
		glm::vec3 mov{ 0,0,0 };
		for (auto im : m_InputMappingMap)
			if (im.second.IsPressed)
				mov += (m_Direction.at(im.second.Name) * m_Speed);
		m_pParent->GetComponent<BodyComponent>()->SetLinearVelocity(mov.x,mov.y);
	}
}

void dae::MovementComponent::OnNotify(const Subject* subject, int, va_list args)
{
	if (subject->GetTag() == "InputManager")
	{
		SDL_EventType event = va_arg(args, SDL_EventType); (event);
		SDL_KeyboardEvent kbEvent = va_arg(args, SDL_KeyboardEvent);

		if (m_InputMappingMap.find(kbEvent.keysym.scancode) != m_InputMappingMap.end())		
			m_InputMappingMap.at(kbEvent.keysym.scancode).IsPressed = kbEvent.state && SDL_PRESSED;
	}
}
