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

void dae::SteamAchievementManager::OnUserStatsReceived(UserStatsReceived_t* pCallback) {
	// we may get callbacks for other games' stats arriving, ignore them
	if (static_cast<uint64>(m_iAppID) == pCallback->m_nGameID) {
		if (k_EResultOK == pCallback->m_eResult) {
			std::cout << "Received stats and achievements from Steam" << std::endl;
			m_bInitialized = true;
		}
	}
}

void dae::SteamAchievementManager::OnUserStatsStored(UserStatsStored_t* pCallback) {
	// we may get callbacks for other games' stats arriving, ignore them
	if (static_cast<uint64>(m_iAppID) == pCallback->m_nGameID) {
		if (k_EResultOK == pCallback->m_eResult) {
			std::cout << "Stored stats for Steam" << std::endl;
		} else {
			std::cout << "Failed to store stats for steam" << std::endl;
		}
	}
}

void dae::SteamAchievementManager::OnAchievementStored(UserAchievementStored_t* pCallback) {
	// we may get callbacks for other games' stats arriving, ignore them
	if (static_cast<uint64>(m_iAppID) == pCallback->m_nGameID) {
		std::cout << "Stored achievement for Steam" << std::endl;
	}
}