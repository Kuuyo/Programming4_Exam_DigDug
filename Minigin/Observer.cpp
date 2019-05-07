#include "MiniginPCH.h"
#include "Observer.h"

dae::Subject::Subject(std::string && tag)
	: m_Tag(std::move(tag))
{
}

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.insert(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	m_Observers.erase(observer);
}

//void dae::Subject::Notify(const GameObject* entity, int eventID) const
//{
//	for (auto observer : m_Observers)
//		observer->OnNotify(entity, eventID);
//}

void dae::Subject::Notify(const Subject* subject, int nrArgs, ...) const
{
	va_list ap;
	va_start(ap, nrArgs);
	for (auto observer : m_Observers)
		observer->OnNotify(subject, nrArgs, ap);
	va_end(ap);
}