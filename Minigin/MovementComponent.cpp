#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include "InputManager.h"
#include "BodyComponent.h"
#include "InfiniteGridComponent.h"

namespace dae
{
	MovementComponent::MovementComponent(float speed, bool lockDiagonal, int playerIndex)
		: MovementComponent(speed, lockDiagonal, false, playerIndex)
	{

	}

	MovementComponent::MovementComponent(float speed, bool lockDiagonal, bool lockToGrid, int playerIndex)
		: m_PlayerIndex(playerIndex)
		, m_Speed(speed)
		, m_IsDiagonalLocked(lockDiagonal)
		, m_IsLockedToGrid(lockToGrid)
	{
		m_Direction.insert({ Direction::Up, glm::vec2(0.f,-1.f) });
		m_Direction.insert({ Direction::Down, glm::vec2(0.f,1.f) });
		m_Direction.insert({ Direction::Left, glm::vec2(-1.f,0.f) });
		m_Direction.insert({ Direction::Right, glm::vec2(1.f,0.f) });
	}

	MovementComponent::~MovementComponent()
	{
		m_pInput->RemoveObserver(this);
	}

	void MovementComponent::Initialize(const SceneContext &sceneContext)
	{
		m_pInput = sceneContext.GameContext->Input;
		m_pInput->AddObserver(this);

		m_bHasBody = m_pParent->HasComponent<BodyComponent>();

		// TODO: Make Input in MovementComponent not hardcoded
		m_InputMappingMap.insert({ SDL_SCANCODE_W, { Direction::Up, false } });
		m_InputMappingMap.insert({ SDL_SCANCODE_S, { Direction::Down, false } });
		m_InputMappingMap.insert({ SDL_SCANCODE_A, { Direction::Left, false } });
		m_InputMappingMap.insert({ SDL_SCANCODE_D, { Direction::Right, false } });
	}

	void MovementComponent::Update(const SceneContext &sceneContext)
	{
		if (!m_bHasBody)
		{
			for (auto im : m_InputMappingMap)
				if (im.second.second)
					m_pParent->SetPosition(
						m_pParent->GetPosition() +
						(m_Direction.at(im.second.first) * sceneContext.GameContext->Time->GetDeltaTime() * m_Speed)
					);
		}
		else if (m_IsLockedToGrid)
		{
			glm::vec2 mov{ 0,0 };

			if (!m_LatestKeys.empty() && m_LatestKeys.back())
			{
				auto im = m_InputMappingMap.at(m_LatestKeys.back());

				auto pos = m_pParent->GetPosition();
				LogDebugC(std::to_string(pos.x) + " " + std::to_string(pos.y));

				if (im.second)
					mov += m_Direction.at(im.first);

				auto dest = pos + mov;

				auto gPoint = m_pParent->GetComponent<InfiniteGridComponent>()->GetClosestGridPoint(dest.x, dest.y, im.first);

				LogDebugC(std::to_string(gPoint.x) + " " + std::to_string(gPoint.y));

				mov = glm::normalize(gPoint - pos);

				LogDebugC(std::to_string(mov.x) + " " + std::to_string(mov.y));

				if (mov.x != 0.f && mov.y != 0.f)
				{
					if (abs(mov.x) > abs(mov.y))
					{
						mov.x = 0.f;
					}
					else
					{
						mov.y = 0.f;
					}
				}

				LogDebugC(std::to_string(mov.x) + " " + std::to_string(mov.y));

				std::cout << std::endl;

				mov *= m_Speed;
			}

			m_pParent->GetComponent<BodyComponent>()->SetLinearVelocity(mov.x, mov.y);
		}
		else if (m_IsDiagonalLocked)
		{
			glm::vec2 mov{ 0,0 };

			if (!m_LatestKeys.empty() && m_LatestKeys.back())
			{
				auto im = m_InputMappingMap.at(m_LatestKeys.back());

				if (im.second)
					mov += (m_Direction.at(im.first) * m_Speed);
			}

			m_pParent->GetComponent<BodyComponent>()->SetLinearVelocity(mov.x, mov.y);
		}
		else
		{
			glm::vec2 mov{ 0,0 };
			for (auto im : m_InputMappingMap)
				if (im.second.second)
					mov += (m_Direction.at(im.second.first) * m_Speed);
			m_pParent->GetComponent<BodyComponent>()->SetLinearVelocity(mov.x, mov.y);
		}

		// TODO: FIX THIS MESS
	}

	void MovementComponent::OnNotify(const Subject* subject, int, va_list args)
	{
		if (subject->GetTag() == "InputManager") // TODO: Decide if this is necessary
		{
			SDL_EventType event = va_arg(args, SDL_EventType); (event);
			SDL_KeyboardEvent kbEvent = va_arg(args, SDL_KeyboardEvent);

			if (m_InputMappingMap.find(kbEvent.keysym.scancode) != m_InputMappingMap.end())
			{
				m_InputMappingMap.at(kbEvent.keysym.scancode).second = kbEvent.state && SDL_PRESSED;

				if (event == SDL_KEYDOWN)
					m_LatestKeys.push_back(kbEvent.keysym.scancode);
				else if (event == SDL_KEYUP)
					m_LatestKeys.erase(std::remove(m_LatestKeys.begin(), m_LatestKeys.end(), kbEvent.keysym.scancode), m_LatestKeys.end());
			}
		}
	}
}