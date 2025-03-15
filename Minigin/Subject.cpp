#include "Subject.h"

dae::Subject::Subject(GameObject* gameObject) : m_gameObject(gameObject) {
}

void dae::Subject::AddObserver(std::weak_ptr<Observer> observer) {
	m_observers.push_back(observer);
}

void dae::Subject::RemoveObserver(std::weak_ptr<Observer> observer) {
	std::erase_if(m_observers, [&observer](const std::weak_ptr<Observer>& other) {
		auto lockedObserver = observer.lock();
		auto lockedOther = other.lock();

		return lockedObserver == lockedOther;
	});
}

void dae::Subject::NotifyObservers(Event event) {
	for (auto& observer : m_observers) {
		// Check if observer is still valid
		if (auto sharedObserver = observer.lock()) {
			sharedObserver->Notify(event, m_gameObject);
		}
	}
}
