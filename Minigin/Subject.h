#pragma once
#include "Observer.h"
namespace dae {
	class Subject {
	public:
		Subject(GameObject* gameObject);

		void AddObserver(std::weak_ptr<Observer> observer);
		void RemoveObserver(std::weak_ptr<Observer> observer);
		void NotifyObservers(Event event);

	private:
		GameObject* m_gameObject;

		std::vector<std::weak_ptr<Observer>> m_observers;
	};
}
