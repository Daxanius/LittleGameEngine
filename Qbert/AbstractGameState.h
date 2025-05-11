#pragma once

namespace dae {
	class Qbert;

	class AbstractGameState {
	public:
		virtual void OnEnter() = 0;

	protected:
		AbstractGameState() = default;
	};
}
