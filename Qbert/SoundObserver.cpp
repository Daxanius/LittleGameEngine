#include "SoundObserver.h"
#include "hash.h"

dae::SoundObserver::SoundObserver() : m_soundSystem(ServiceLocator::GetInstance().GetSoundSystem()) {
	m_changeSelectionSfx = m_soundSystem.RegisterSound("../Data/Sounds/Change Selection.wav");
	m_qbertJumpSfx = m_soundSystem.RegisterSound("../Data/Sounds/QBert Jump.wav");
	m_discLandSfx = m_soundSystem.RegisterSound("../Data/Sounds/Disk Land.wav");
	m_discLiftSfx = m_soundSystem.RegisterSound("../Data/Sounds/Disk Lift.wav");
	m_roundCompleteSfx = m_soundSystem.RegisterSound("../Data/Sounds/Round Complete Tune.wav");
	m_swearingSfx = m_soundSystem.RegisterSound("../Data/Sounds/Swearing.wav");
	m_slickSamCaughtSfx = m_soundSystem.RegisterSound("../Data/Sounds/SlickSam Caught.wav");
	m_coilyFallSfx = m_soundSystem.RegisterSound("../Data/Sounds/Coily Fall.wav");
	m_coilyEggJumpSfx = m_soundSystem.RegisterSound("../Data/Sounds/Coily Egg Jump.wav");
	m_coilySnakeJumpSfx = m_soundSystem.RegisterSound("../Data/Sounds/Coily Snake Jump.wav");
	m_enemyJumpSfx = m_soundSystem.RegisterSound("../Data/Sounds/Other Foes Jump.wav");
}

void dae::SoundObserver::Notify(const Event& event) {
	switch (event.id) {
		case make_sdbm_hash("menu_previous"):
		case make_sdbm_hash("menu_next"):
			Play(m_changeSelectionSfx);
			break;
		case make_sdbm_hash("arrive"):
			Play(m_qbertJumpSfx);
			break;
		case make_sdbm_hash("disc_lift"):
			Play(m_discLiftSfx);
			break;
		case make_sdbm_hash("disc_land"):
			Play(m_discLandSfx);
			break;
		case make_sdbm_hash("killed"):
			Play(m_swearingSfx);
			break;
		case make_sdbm_hash("next_round"):
			Play(m_roundCompleteSfx);
			break;
		case make_sdbm_hash("slicksam_caught"):
			Play(m_slickSamCaughtSfx);
			break;
		case make_sdbm_hash("enemy_jump"):
			Play(m_enemyJumpSfx);
			break;
		case make_sdbm_hash("coily_fall"):
			Play(m_coilyFallSfx);
			break;
		case make_sdbm_hash("ball_jump"):
			Play(m_coilyEggJumpSfx);
			break;
		case make_sdbm_hash("snake_jump"):
			Play(m_coilySnakeJumpSfx);
			break;
	}
}

void dae::SoundObserver::Play(SoundId sound) const {
	m_soundSystem.Play(sound, m_volume);
}
