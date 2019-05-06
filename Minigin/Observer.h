#pragma once
#include <set>

namespace dae
{
	class GameObject;

	// http://www.gameprogrammingpatterns.com/observer.html

	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void OnNotify(const GameObject* entity, int eventID) = 0;
	};

	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

	protected:
		void Notify(const GameObject* entity, int eventID) const;

	private:
		std::set<Observer*> m_Observers;
	};
}