#pragma once
#include <any>
#include <optional>
#include <string>

namespace dae {
	using EventId = unsigned int;

	struct Event {
		// We don't need a list of args if we can just have
		// any data be passed, it can provide all necessary
		// information.
		// std::any already provides "empty" state, meaning it can be optional
		std::any data;


		const EventId id;

		template<typename DataType>
		[[nodiscard]] inline DataType GetValue() const {
			return std::any_cast<DataType>(data);
		};

		explicit Event(EventId id) : id(id) {};
	};
}