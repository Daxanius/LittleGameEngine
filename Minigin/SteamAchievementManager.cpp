#include "SteamAchievementManager.h"
#include <iostream>

dae::SteamAchievementManager::SteamAchievementManager() :
	m_iAppID(0),
	m_bInitialized(false),
	m_CallbackUserStatsReceived(this, &SteamAchievementManager::OnUserStatsReceived),
	m_CallbackUserStatsStored(this, &SteamAchievementManager::OnUserStatsStored),
	m_CallbackAchievementStored(this, &SteamAchievementManager::OnAchievementStored)
{
	m_iAppID = SteamUtils()->GetAppID();
	RequestStats();
}

bool dae::SteamAchievementManager::RequestStats() {
	// Is Steam loaded? If not we can't get stats.
	if (NULL == SteamUserStats() || NULL == SteamUser()) {
		return false;
	}
	// Is the user logged on?  If not we can't get stats.
	if (!SteamUser()->BLoggedOn()) {
		return false;
	}
	// Request user stats.
	return SteamUserStats()->RequestCurrentStats();
}

bool dae::SteamAchievementManager::SetAchievement(const char* ID) {
	// Have we received a call back from Steam yet?
	if (m_bInitialized) {
		SteamUserStats()->SetAchievement(ID);
		return SteamUserStats()->StoreStats();
	}

	// If not then we can't set achievements yet
	return false;
}

void dae::SteamAchievementManager::OnUserStatsReceived(UserStatsReceived_t*) {
	// we may get callbacks for other games' stats arriving, ignore them
}

void dae::SteamAchievementManager::OnUserStatsStored(UserStatsStored_t*) {
	// we may get callbacks for other games' stats arriving, ignore them
}

void dae::SteamAchievementManager::OnAchievementStored(UserAchievementStored_t*) {
	// we may get callbacks for other games' stats arriving, ignore them
}