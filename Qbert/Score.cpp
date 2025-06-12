#include "Score.h"
#include <fstream>

nlohmann::json dae::Score::ToJson() const {
    return nlohmann::json{
        {"name", name},
        {"score", score}
    };
}

void dae::Score::ToFile(const std::vector<Score>& scores, const std::string& path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + path);
    }

    nlohmann::json j = nlohmann::json::array();
    for (const auto& score : scores) {
        j.push_back({
            {"name", score.name},
            {"score", score.score}
        });
    }

		// pretty print with 4-space indentation
    file << j.dump(4); 
}

dae::Score dae::Score::FromJson(const dae::json& json) {
	return Score{
			json.at("name").get<std::string>(),
			json.at("score").get<int>()
	};
}

std::vector<dae::Score> dae::Score::FromFile(const std::string& path) {
	  std::ifstream file(path);
    json json;
    file >> json;

    std::vector<Score> scores;
    for (const auto& scoreJson : json) {
        scores.emplace_back(Score::FromJson(scoreJson));
    }
    return scores;
}