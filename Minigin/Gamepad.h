#pragma once

#include <memory>
#include <variant>
#include <optional>
#include <vector>

#include <functional>
#include <unordered_map>

namespace dae {
	class Gamepad final {
	public:
		enum class Button {
			Start,
			Back,
			LeftThumb,
			RightThumb,
			LeftShoulder,
			RightShoulder,
			Up,
			Down,
			Left,
			Right,
			A,
			B,
			X,
			Y
		};

		enum class ActionType {
			None,
			Press,
			Hold,
			Release
		};

		struct ButtonState {
			Button button;
			ActionType actionType;
		};

		struct ButtonStateHash {
			std::size_t operator()(const ButtonState& bs) const {
				std::size_t h1 = std::hash<int>()(static_cast<int>(bs.button));
				std::size_t h2 = std::hash<int>()(static_cast<int>(bs.actionType));
				return h1 ^ (h2 << 1);
			}
		};

		Gamepad(unsigned long controllerId);
		~Gamepad();

		void UpdateState();

		[[nodiscard]] const std::vector<ButtonState>& GetButtonStates() const;

		[[nodiscard]] bool IsConnected() const;
	private:
		// The gamepad implementation to use
		class impl;
		std::unique_ptr<impl> m_pImpl;
	};

	inline bool operator==(const Gamepad::ButtonState& lhs, const Gamepad::ButtonState& rhs) {
		return lhs.button == rhs.button && lhs.actionType == rhs.actionType;
	}
}