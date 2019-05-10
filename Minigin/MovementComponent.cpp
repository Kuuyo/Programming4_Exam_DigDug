#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "Time.h"
#include "InputManager.h"
#include "BodyComponent.h"

dae::MovementComponent::MovementComponent(float speed, bool lockDiagonal, int playerIndex)
	:m_PlayerIndex(playerIndex)
	,m_Speed(speed)
	,m_IsDiagonalLocked(lockDiagonal)
{
	m_Direction.insert({ "Up",glm::vec3(0.f,-1.f,0.f) });
	m_Direction.insert({ "Down",glm::vec3(0.f,1.f,0.f) });
	m_Direction.insert({ "Left",glm::vec3(-1.f,0.f,0.f) });
	m_Direction.insert({ "Right",glm::vec3(1.f,0.f,0.f) });
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
	else if (m_IsDiagonalLocked)
	{
		glm::vec3 mov{ 0,0,0 };

		if (!m_LatestKeys.empty() && m_LatestKeys.back())
		{
			dae::InputMapping im = m_InputMappingMap.at(m_LatestKeys.back());

			if (im.IsPressed)
				mov += (m_Direction.at(im.Name) * m_Speed);
		}		

		m_pParent->GetComponent<BodyComponent>()->SetLinearVelocity(mov.x, mov.y);
	}
	else
	{
		glm::vec3 mov{ 0,0,0 };
		for (auto im : m_InputMappingMap)
			if (im.second.IsPressed)
				mov += (m_Direction.at(im.second.Name) * m_Speed);
		m_pParent->GetComponent<BodyComponent>()->SetLinearVelocity(mov.x,mov.y);
	}

	// TODO: FIX THIS MESS
}

void dae::MovementComponent::OnNotify(const Subject* subject, int, va_list args)
{
	if (subject->GetTag() == "InputManager") // TODO: Decide if this is necessary
	{
		SDL_EventType event = va_arg(args, SDL_EventType); (event);
		SDL_KeyboardEvent kbEvent = va_arg(args, SDL_KeyboardEvent);

		if (m_InputMappingMap.find(kbEvent.keysym.scancode) != m_InputMappingMap.end())
		{
			m_InputMappingMap.at(kbEvent.keysym.scancode).IsPressed = kbEvent.state && SDL_PRESSED;

			if (event == SDL_KEYDOWN)
				m_LatestKeys.push_back(kbEvent.keysym.scancode);
			else if (event == SDL_KEYUP)
				m_LatestKeys.erase(std::remove(m_LatestKeys.begin(), m_LatestKeys.end(), kbEvent.keysym.scancode), m_LatestKeys.end());
		}
	}
}
