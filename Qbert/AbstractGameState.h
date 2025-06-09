#pragma once

namespace dae {
	class Qbert;

	class AbstractGameState {
	public:
		virtual void OnEnter() = 0;


		AbstractGameState(const AbstractGameState&) = delete;
		AbstractGameState& operator=(const AbstractGameState&) = delete;
		AbstractGameState(AbstractGameState&&) = delete;
		AbstractGameState& operator=(AbstractGameState&&) = delete;
		~AbstractGameState() = default;
	protected:
		AbstractGameState() = default;
	};
}
