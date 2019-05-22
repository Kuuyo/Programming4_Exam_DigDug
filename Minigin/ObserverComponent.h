#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <functional>

namespace dae
{
	class ObserverComponent : public BaseComponent, public Observer
	{
	public:
		ObserverComponent() = default;

		void AddFunction(std::function<void(const dae::Subject* entity, int nrArgs, va_list args)> &func);

		ObserverComponent(const ObserverComponent&) = delete;
		ObserverComponent(ObserverComponent&&) = delete;
		ObserverComponent& operator= (const ObserverComponent&) = delete;
		ObserverComponent& operator= (const ObserverComponent&&) = delete;

	protected:
		void OnNotify(const dae::Subject* entity, int nrArgs, va_list args) override;

		void Initialize(const SceneContext &) override {}
		void Update(const SceneContext &) override {}
		void LateUpdate(const SceneContext &) override {}

		~ObserverComponent() = default;

		std::vector<std::function<void(const dae::Subject* entity, int nrArgs, va_list args)>> m_Functions;
	};
}