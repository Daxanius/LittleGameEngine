#include "PlaySoundCommand.h"

dae::PlaySoundCommand::PlaySoundCommand(GameObject* actor, const std::string& file, float volume) : ActorCommand(actor), m_volume(volume) {
	ServiceLocator::GetInstance().GetSoundSystem().RegisterSound(file);
}

void dae::PlaySoundCommand::Execute() {
	ServiceLocator::GetInstance().GetSoundSystem().Play(m_soundId, m_volume);
}
