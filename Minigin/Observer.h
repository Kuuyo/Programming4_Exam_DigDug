#pragma once
#include <set>

namespace dae
{
	class GameObject;
	class Observer;

	// http://www.gameprogrammingpatterns.com/observer.html


	class Subject
	{
	public:
		Subject(std::string &&tag);

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

		const std::string GetTag() const { return m_Tag; }

	protected:
		//void Notify(const GameObject* entity, int eventID) const;
		void Notify(const Subject* subject, int nrArgs, ...) const;

	private:
		std::set<Observer*> m_Observers;
		std::string m_Tag;
	};

	class Observer
	{
	public:
		virtual ~Observer() {}
		//virtual void OnNotify(const GameObject* entity, int eventID) = 0;
		virtual void OnNotify(const Subject* entity, int nrArgs, va_list args) = 0;
	};
}