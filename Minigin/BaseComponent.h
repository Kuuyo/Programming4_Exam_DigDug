#pragma once

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent &) = delete;
		BaseComponent(BaseComponent &&) = delete;
		BaseComponent & operator= (const BaseComponent &) = delete;
		BaseComponent & operator= (const BaseComponent &&) = delete;

	protected:
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

		GameObject* m_pParent;

	private:
		friend GameObject;
	};
}