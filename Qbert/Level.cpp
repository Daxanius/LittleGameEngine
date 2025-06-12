#include "Level.h"
#include <fstream>

dae::Enemy dae::Enemy::FromJson(const json& json) {
    return Enemy{
        json.at("type").get<std::string>(),
        json.at("count").get<int>(),
				json.at("delay").get<float>()
    };
}

dae::Round dae::Round::FromJson(const json& json) {
	Round round{};
  round.discs = json.at("discs").get<int>();
	round.variant = json.at("variant").get<int>();

  for (const auto& enemyJson : json.at("enemies")) {
      round.enemies.emplace_back(Enemy::FromJson(enemyJson));
  }

  return round;
}

dae::Level dae::Level::FromJson(const json& json) {
	Level level{};
  level.icon = json.at("icon").get<std::string>();
	level.tileBehavior = json.at("tile_behavior").get<std::string>();

  for (const auto& roundJson : json.at("rounds")) {
      level.rounds.emplace_back(Round::FromJson(roundJson));
  }

  return level;
}


std::vector<dae::Level> dae::Level::FromFile(const std::string& path) {
    std::ifstream file(path);
    json json;
    file >> json;

    std::vector<Level> levels;
    for (const auto& levelJson : json) {
        levels.emplace_back(Level::FromJson(levelJson));
    }
    return levels;
}
