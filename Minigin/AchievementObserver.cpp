#include "AchievementObserver.h"
#include "GameObject.h"
#include "hash.h"
#include "SteamAchievementManager.h"
#include <iostream>

void dae::AchievementObserver::Notify(Event event, GameObject*) {
	switch (event.id) {
		case make_sdbm_hash("score_increased"):
		{
			std::pair<int, int> score{ any_cast<std::pair<int, int>>(event.data) };

			if (score.second >= 500) {
				SteamAchievementManager::GetInstance().SetAchievement("NEW_ACHIEVEMENT_0_4");
			}

			break;
		}

	}
}
