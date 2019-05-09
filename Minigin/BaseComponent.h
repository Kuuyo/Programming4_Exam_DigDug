#pragma once

namespace dae
{
	class GameObject;
	struct GameContext;

	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		GameObject* GetGameObject() { return m_pParent; }

		BaseComponent(const BaseComponent &) = delete;
		BaseComponent(BaseComponent &&) = delete;
		BaseComponent & operator= (const BaseComponent &) = delete;
		BaseComponent & operator= (const BaseComponent &&) = delete;

	protected:
		virtual void Initialize(const GameContext &gameContext) = 0;
		virtual void Update(const GameContext &gameContext) = 0;

		GameObject* m_pParent;

	private:
		friend GameObject;
	};
}