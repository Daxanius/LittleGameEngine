#include "SoundObserver.h"
#include "hash.h"

dae::SoundObserver::SoundObserver() {
	m_changeSelectionSfx = ServiceLocator::GetInstance().GetSoundSystem().RegisterSound("../Data/Sounds/Change Selection.wav");
}

void dae::SoundObserver::Notify(Event event) {
	switch (event.id) {
		case make_sdbm_hash("menu_previous"):
		case make_sdbm_hash("menu_next"):
			ServiceLocator::GetInstance().GetSoundSystem().Play(m_changeSelectionSfx, m_volume);
			break;
	}
}
