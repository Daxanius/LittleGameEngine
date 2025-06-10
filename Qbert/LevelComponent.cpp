#include "LevelComponent.h"
#include "PlayerComponent.h"
#include "hash.h"

dae::LevelComponent::LevelComponent(GameObject& pOwner, float resetTime) : BaseComponent(pOwner), m_resetTime(resetTime) {
	m_pRhombilleGrid = GetOwner().GetComponent<RhombilleGridComponent>();
}

void dae::LevelComponent::NextRound() {
	// Go to the next round
	m_Round++;

	// If it's larger or equal to the rounds per level,
	// reset it, go to the next level, and notify the subject
	if (m_Round >= ROUNDS_PER_LEVEL) {
		m_Level++;
		m_Round = 0;
		Event nextLevelEvent{ make_sdbm_hash("next_level") };
		nextLevelEvent.data = m_Level;
		m_Subject.Notify(std::move(nextLevelEvent));
		return;
	}

	// Otherwise notify subjects the next round has been triggered
	Event nextRoundEvent{ make_sdbm_hash("next_round") };
	nextRoundEvent.data = m_Round;
	m_Subject.Notify(std::move(nextRoundEvent));
}

int dae::LevelComponent::GetRound() const {
	return m_Round;
}

int dae::LevelComponent::GetLevel() const {
	return m_Level;
}

void dae::LevelComponent::PauseLevel() {
	m_Paused = true;
}

void dae::LevelComponent::UnpauseLevel() {
	m_Paused = false;
}

void dae::LevelComponent::ResetLevel(bool resetState) {
	m_InResetAnimation = true;
	m_ShouldResetState = resetState;
	m_resetTimeLeft = m_resetTime;

	for (auto player : m_Players) {
		player->GetOwner().Disable();
	}
}

bool dae::LevelComponent::LevelPaused() const {
	return m_Paused || m_InResetAnimation;
}

bool dae::LevelComponent::InResetAnimation() const {
	return m_InResetAnimation;
}

void dae::LevelComponent::RegisterPlayer(PlayerComponent* pPlayer) {
	m_Players.emplace_back(pPlayer);
}

void dae::LevelComponent::RegisterSpawner(EnemySpawnerComponent* pSpawner) {
	m_pEnemySpawner = pSpawner;
}

void dae::LevelComponent::AddGameOverCommand(std::unique_ptr<Command>&& pCommand) {
	m_gameOverCommands.emplace_back(std::forward<std::unique_ptr<Command>>(pCommand));
}

dae::Subject& dae::LevelComponent::GetSubject() {
	return m_Subject;
}

dae::RhombilleGridComponent& dae::LevelComponent::GetRhombilleGrid() {
	return *m_pRhombilleGrid;
}

dae::EnemySpawnerComponent& dae::LevelComponent::GetEnemySpawner() {
	return *m_pEnemySpawner;
}

void dae::LevelComponent::Update(float deltaTime) {
	if (!m_InResetAnimation) {
		return;
	}

	if (m_resetTimeLeft <= 0.f) {
		m_InResetAnimation = false;

		if (m_ShouldResetState) {
			m_pRhombilleGrid->SetAllStates(0);
		}

		for (auto player : m_Players) {
			player->GetOwner().Enable();
			player->Reset(); // Reset the player component

			if (player->GetLivesComponent()->GetLives() <= 0) {
				for (auto& command : m_gameOverCommands) {
					command->Execute();
				}
			}
		}

		if (m_pEnemySpawner != nullptr) {
			m_pEnemySpawner->KillAllEnemies();
		}
	}

	m_resetTimeLeft -= deltaTime;
}

const std::vector<dae::PlayerComponent*>& dae::LevelComponent::GetPlayers() const {
	return m_Players;
}
