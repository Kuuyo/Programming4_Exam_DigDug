#pragma once

namespace dae
{
	class GameObject;
	struct SceneContext;

	class BaseComponent
	{
	public:
		BaseComponent() = default;

		GameObject* GetGameObject() { return m_pParent; }

		BaseComponent(const BaseComponent &) = delete;
		BaseComponent(BaseComponent &&) = delete;
		BaseComponent & operator= (const BaseComponent &) = delete;
		BaseComponent & operator= (const BaseComponent &&) = delete;

	protected:
		virtual ~BaseComponent() = default;

		virtual void Initialize(const SceneContext &sceneContext) = 0;
		virtual void Update(const SceneContext &sceneContext) = 0;
		virtual void LateUpdate(const SceneContext &sceneContext) = 0;

		GameObject* m_pParent;

	private:
		friend GameObject;
	};
}