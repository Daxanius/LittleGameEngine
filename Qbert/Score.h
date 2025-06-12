#pragma once
#include <string>
#include <vector>
#include "json.hpp"

namespace dae {
	using json = nlohmann::json;

	struct Score {
		std::string name;
		int score;

		json ToJson() const;
		static void ToFile(const std::vector<Score>& scores, const std::string& path);

		static Score FromJson(const json& json);
		static std::vector<Score> FromFile(const std::string& path);
	};
}