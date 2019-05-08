#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <map>
#include "Structs.h"

namespace dae
{
	class InputManager;

	class MovementComponent final : public BaseComponent, public Observer
	{
	public:
		MovementComponent(int playerIndex = 0);
		virtual ~MovementComponent();

		MovementComponent(const MovementComponent &) = delete;
		MovementComponent(MovementComponent &&) = delete;
		MovementComponent & operator= (const MovementComponent &) = delete;
		MovementComponent & operator= (const MovementComponent &&) = delete;

		void Initialize(const GameContext &gameContext) override;
		void Update(const GameContext &gameContext) override;

	private:
		bool m_bHasBody = false;

		InputManager* m_pInput;
		UINT m_PlayerIndex;
		float m_Speed;
		std::map<SDL_Scancode, InputMapping> m_InputMappingMap;
		std::map<std::string, glm::vec3> m_Direction;

		void OnNotify(const Subject* subject, int nrArgs, va_list args) override;
	};
}