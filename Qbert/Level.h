#pragma once
#include <string>
#include <vector>
#include "json.hpp"

namespace dae {
	using json = nlohmann::json;

	struct Enemy {
			std::string type;
			int count;
			float delay;

			static Enemy FromJson(const json& json);
	};

	struct Round {
			int discs;
			int variant;
			std::vector<Enemy> enemies;

			static Round FromJson(const json& json);
	};

	struct Level {
			std::string icon;
			std::string tileBehavior;
			int requiredTileState;
			std::vector<Round> rounds;

			static Level FromJson(const json& json);

			static std::vector<Level> FromFile(const std::string& path);
	};
}