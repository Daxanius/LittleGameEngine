#pragma once

namespace dae {
	struct SteamAchievement {
		int Id;
		const char* chID;
		char name[128];
		char description[256];
		bool achieved;
		int iconImage;
	};
}