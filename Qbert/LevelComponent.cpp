#include "LevelComponent.h"
#include "hash.h"
#include "Subject.h"
#include "RhombilleGridComponent.h"
#include "PlayerComponent.h"
#include "EnemySpawnerComponent.h"
#include "SpinningDiscComponent.h"
#include "Command.h"
#include "Scene.h"
#include "SceneManager.h"

dae::LevelComponent::LevelComponent(GameObject& pOwner, float resetTime) : BaseComponent(pOwner), m_resetTime(resetTime) {
	m_pRhombilleGrid = GetOwner().GetComponent<RhombilleGridComponent>();
}

void dae::LevelComponent::NextRound() {
	// Go to the next round
	m_Round++;

	// If it's larger or equal to the rounds per level,
	// reset it, go to the next level, and notify the subject
	if (m_Round >= ROUNDS_PER_LEVEL) {
		m_Round = 0;
		m_Subject.Notify("next_level");
		return;
	}

	// Otherwise notify subjects the next round has been triggered
	m_Subject.Notify("next_round", m_Round);
}

int dae::LevelComponent::GetRound() const {
	return m_Round;
}

void dae::LevelComponent::PauseLevel() {
	m_Paused = true;
}

void dae::LevelComponent::UnpauseLevel() {
	m_Paused = false;
}

bool dae::LevelComponent::CheckSpinningDiscs() {
	for (auto player : m_Players) {
		auto movementComponent{ player->GetMovementComponent() };
		if (movementComponent->IsJumping()) {
			continue;
		}

		for (auto disc : m_spinningDiscs) {
			if (disc->IsTransportingPlayer()) {
				continue;
			}

			if (disc->GetRow() == movementComponent->GetRow() && disc->GetCol() == movementComponent->GetCol()) {
				disc->TransportPlayer(player);
				return true;
			}
		}
	}

	return false;
}

void dae::LevelComponent::ResetLevel(bool resetState) {
	m_InResetAnimation = true;
	m_ShouldResetState = resetState;
	m_resetTimeLeft = m_resetTime;

	SpawnSpinningDiscs();
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

void dae::LevelComponent::PostUpdate() {
	// Remove any potentially destroyed spinning discs from the list
	m_spinningDiscs.erase(
		std::remove_if(m_spinningDiscs.begin(), m_spinningDiscs.end(),
			[](SpinningDiscComponent* disc) {
				return disc->GetOwner().IsDestroyed();
			}), m_spinningDiscs.end()
	);
}

const std::vector<dae::PlayerComponent*>& dae::LevelComponent::GetPlayers() const {
	return m_Players;
}

void dae::LevelComponent::SpawnSpinningDiscs() {
	for (size_t discIndex{ m_spinningDiscs.size() }; discIndex < m_totalSpinningDiscs; discIndex++) {
		auto discObject{ std::make_unique<GameObject>() };
		auto pSpriteComponent{ discObject->AddComponent<SpriteComponent>("Disk Spritesheet.png", 16, 10, 2.f) };
		m_spinningDiscs.emplace_back(discObject->AddComponent<SpinningDiscComponent>(m_pRhombilleGrid, 3, 4));

		int variant{ m_pRhombilleGrid->GetVariant() };
		pSpriteComponent->AddState(make_sdbm_hash("idle"), SpriteComponent::State{ variant * 5, 0, 4, 10 });

		pSpriteComponent->SetState(make_sdbm_hash("idle"));

		SceneManager::GetInstance().GetActiveScene()->Add(std::move(discObject));
	}
}
