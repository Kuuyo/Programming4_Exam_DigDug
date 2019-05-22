#include "MiniginPCH.h"
#include "ObserverComponent.h"

namespace dae
{
	void ObserverComponent::AddFunction(std::function<void(const dae::Subject* entity, int nrArgs, va_list args)>& func)
	{
		m_Functions.push_back(func);
	}

	void ObserverComponent::OnNotify(const dae::Subject* entity, int nrArgs, va_list args)
	{
		for (const auto& f : m_Functions)
			f(entity, nrArgs, args);
	}
}