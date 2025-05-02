#pragma once

#include <memory>
#include<vector>
#include "Observer.h"

namespace dae {
	class Subject {
	public:
		Subject() = default;

		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);
		void Notify(Event event);

		Subject(const Subject&) = delete;
		Subject& operator=(const Subject&) = delete;
		Subject(Subject&&) = delete;
		Subject& operator=(Subject&&) = delete;
		~Subject() = default;
	private:
		std::vector<std::shared_ptr<Observer>> m_observers;
	};
}
