#include "MiniginPCH.h"
#include "Observer.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.insert(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	m_Observers.erase(observer);
}

void dae::Subject::Notify(const GameObject* entity, int eventID) const
{
	for (auto observer : m_Observers)
		observer->OnNotify(entity, eventID);
}
