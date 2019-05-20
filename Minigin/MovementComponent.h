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
		MovementComponent(float speed, bool lockDiagonal = true, int playerIndex = 0);
		MovementComponent(float speed, bool lockDiagonal, bool lockToGrid, int playerIndex = 0);

		MovementComponent(const MovementComponent &) = delete;
		MovementComponent(MovementComponent &&) = delete;
		MovementComponent & operator= (const MovementComponent &) = delete;
		MovementComponent & operator= (const MovementComponent &&) = delete;

	protected:
		void Initialize(const SceneContext &sceneContext) override;
		void Update(const SceneContext &sceneContext) override;
		void LateUpdate(const SceneContext &) override {}

		virtual ~MovementComponent();

	private:
		bool m_bHasBody = false;
		bool m_IsDiagonalLocked;
		bool m_IsLockedToGrid;

		InputManager* m_pInput;
		UINT m_PlayerIndex;
		float m_Speed;
		std::map<SDL_Scancode, std::pair<Direction, bool>> m_InputMappingMap;
		std::map<Direction, glm::vec2> m_Direction;

		std::vector<SDL_Scancode> m_LatestKeys;

		void OnNotify(const Subject* subject, int nrArgs, va_list args) override;
	};
}