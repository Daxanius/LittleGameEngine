#include "ToggleSoundCommand.h"
#include "ServiceLocator.h"

void dae::ToggleSoundCommand::Execute() {
	auto& soundSystem{ ServiceLocator::GetInstance().GetSoundSystem() };
	soundSystem.SetMuted(!soundSystem.IsMuted());
}
