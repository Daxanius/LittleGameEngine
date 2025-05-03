#include "PlaySoundCommand.h"

dae::PlaySoundCommand::PlaySoundCommand(const std::string& file, float volume) : Command(), m_volume(volume) {
	m_soundId = ServiceLocator::GetInstance().GetSoundSystem().RegisterSound(file);
}

void dae::PlaySoundCommand::Execute() {
	ServiceLocator::GetInstance().GetSoundSystem().Play(m_soundId, m_volume);
}
