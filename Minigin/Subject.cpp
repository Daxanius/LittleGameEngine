#include "Subject.h"

void dae::Subject::AddObserver(std::shared_ptr<Observer> observer) {
	m_observers.push_back(observer);
}

void dae::Subject::RemoveObserver(std::shared_ptr<Observer> observer) {
	std::erase_if(m_observers, [&observer](const std::shared_ptr<Observer>& other) {
		return observer == other;
	});
}

void dae::Subject::Notify(Event event) {
	for (auto& observer : m_observers) {
		observer->Notify(event);
	}
}
