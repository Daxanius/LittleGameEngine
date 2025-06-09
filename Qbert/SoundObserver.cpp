#include "SoundObserver.h"
#include "hash.h"

dae::SoundObserver::SoundObserver() {
	auto& soundSystem{ ServiceLocator::GetInstance().GetSoundSystem() };
	m_changeSelectionSfx = soundSystem.RegisterSound("../Data/Sounds/Change Selection.wav");
	m_qbertJumpSfx = soundSystem.RegisterSound("../Data/Sounds/QBert Jump.wav");
}

void dae::SoundObserver::Notify(const Event& event) {
	switch (event.id) {
		case make_sdbm_hash("menu_previous"):
		case make_sdbm_hash("menu_next"):
			ServiceLocator::GetInstance().GetSoundSystem().Play(m_changeSelectionSfx, m_volume);
			break;
		case make_sdbm_hash("arrive"):
			ServiceLocator::GetInstance().GetSoundSystem().Play(m_qbertJumpSfx, m_volume);
			break;
	}
}
