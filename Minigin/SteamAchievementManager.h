#pragma once
#include <steam_api.h>

#include "SteamAchievement.h"
#include "Singleton.h"

namespace dae {
	class SteamAchievementManager : public Singleton<SteamAchievementManager> {
	public:
		SteamAchievementManager();

		bool RequestStats();
		bool SetAchievement(const char* ID);

		STEAM_CALLBACK(SteamAchievementManager, OnUserStatsReceived, UserStatsReceived_t,
									 m_CallbackUserStatsReceived);
		STEAM_CALLBACK(SteamAchievementManager, OnUserStatsStored, UserStatsStored_t,
									 m_CallbackUserStatsStored);
		STEAM_CALLBACK(SteamAchievementManager, OnAchievementStored,
									 UserAchievementStored_t, m_CallbackAchievementStored);

	private:
		int64 m_iAppID; // Our current AppID
		bool m_bInitialized; // Have we called Request stats and received the callback?
	};
}

