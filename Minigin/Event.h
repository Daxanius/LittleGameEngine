#pragma once
#include <any>
#include <optional>
#include <string>

namespace dae {
	using EventId = unsigned int;

	struct Event {
		const EventId id;

		// We don't need a list of args if we can just have
		// any data be passed, it can provide all necessary
		// information.
		// std::any already provides "empty" state, meaning it can be optional
		std::any data;

		explicit Event(EventId id) : id(id) {};
	};
}