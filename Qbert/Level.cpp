#include "Level.h"
#include <fstream>

dae::Enemy dae::Enemy::FromJson(const json& j) {
    return Enemy{
        j.at("type").get<std::string>(),
        j.at("count").get<int>()
    };
}

dae::Round dae::Round::FromJson(const json& j) {
    Round round;
    round.discs = j.at("discs").get<int>();

    for (const auto& enemyJson : j.at("enemies")) {
        round.enemies.emplace_back(Enemy::FromJson(enemyJson));
    }

    return round;
}

dae::Level dae::Level::FromJson(const json& j) {
    Level level;
    level.icon = j.at("icon").get<std::string>();

    for (const auto& roundJson : j.at("rounds")) {
        level.rounds.emplace_back(Round::FromJson(roundJson));
    }

    return level;
}


std::vector<dae::Level> dae::Level::FromFile(const std::string& path) {
    std::ifstream file(path);
    json j;
    file >> j;

    std::vector<Level> levels;
    for (const auto& levelJson : j) {
        levels.emplace_back(Level::FromJson(levelJson));
    }
    return levels;
}
