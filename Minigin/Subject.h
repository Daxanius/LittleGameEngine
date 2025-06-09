#pragma once

#include <memory>
#include<vector>
#include "Observer.h"
#include "hash.h"

namespace dae {
	class Subject {
	public:
		Subject() = default;

		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);

		void Notify(Event&& event);

		template <size_t N> inline void Notify(const char(&text)[N]) {
			Event event{ make_sdbm_hash(text) };
			Notify(std::move(event));
		}

		// This one is overloaded because I don't want
		// to be forced to provide a template type for every event
		// since not all events have data
		template<size_t N, typename EventData>
		void Notify(const char(&text)[N], EventData&& data) {
			Event event{ make_sdbm_hash(text) };
			event.data = std::forward<EventData>(data);
			Notify(std::move(event));
		}

		Subject(const Subject&) = delete;
		Subject& operator=(const Subject&) = delete;
		Subject(Subject&&) = delete;
		Subject& operator=(Subject&&) = delete;
		~Subject() = default;
	private:
		std::vector<std::shared_ptr<Observer>> m_observers;
	};
}
