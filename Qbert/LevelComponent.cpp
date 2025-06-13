#include "LevelComponent.h"
#include "hash.h"
#include "Subject.h"
#include "RhombilleGridComponent.h"
#include "PlayerComponent.h"
#include "EnemySpawnerComponent.h"
#include "SpinningDiscComponent.h"
#include "Command.h"
#include "Scene.h"
#include "RhombilleGridAnimationComponent.h"
#include "SceneManager.h"
#include "Qbert.h"
#include <iostream>

dae::LevelComponent::LevelComponent(GameObject& pOwner, float resetTime, const Level& levelInfo) 
	: BaseComponent(pOwner), m_resetTime(resetTime), m_levelInfo(levelInfo) {
	m_pRhombilleGrid = GetComponent<RhombilleGridComponent>();
	m_pRhombilleGridAnimationComponent = GetComponent<RhombilleGridAnimationComponent>();
}

bool dae::LevelComponent::NextRound() {
	// Go to the next round
	m_round++;

	// If it's larger or equal to the rounds per level,
	// reset it, go to the next level, and notify the subject
	if (m_round >= static_cast<int>(m_levelInfo.rounds.size())) {
		if (m_spinningDiscs.size() > 0) {
			for (auto player : m_Players) {
				player->GetScoreComponent()->AddToScore(50);
			}
		}

		for (auto& command : m_nextLevelCommands) {
			command->Execute();
		}
		return false;
	}

	const auto& enemies = m_levelInfo.rounds[m_round].enemies;
	m_pEnemySpawner->PrepareEnemies(enemies);

	m_hasUpdated = false;
	ResetLevel();

	// Otherwise notify subjects the next round has been triggered
	m_Subject.Notify("next_round", m_round);
	return true;
}

int dae::LevelComponent::GetRound() const {
	return m_round;
}

int dae::LevelComponent::GetTileVariant() const {
	return m_levelInfo.rounds[m_round].variant;
}

void dae::LevelComponent::PauseLevel() {
	m_paused = true;
}

void dae::LevelComponent::UnpauseLevel() {
	m_paused = false;
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

void dae::LevelComponent::ResetLevel() {
	m_inResetAnimation = true;
	m_resetTimeLeft = m_resetTime;
}

bool dae::LevelComponent::LevelPaused() const {
	return m_paused || m_inResetAnimation;
}

bool dae::LevelComponent::InResetAnimation() const {
	return m_inResetAnimation;
}

void dae::LevelComponent::RegisterPlayer(PlayerComponent* pPlayer) {
	m_Players.emplace_back(pPlayer);
}

void dae::LevelComponent::RegisterSpawner(EnemySpawnerComponent* pSpawner) {
	m_pEnemySpawner = pSpawner;
	const auto& enemies = m_levelInfo.rounds[m_round].enemies;
	m_pEnemySpawner->PrepareEnemies(enemies);
}

void dae::LevelComponent::AddNextLevelCommand(std::unique_ptr<Command> pCommand) {
	m_nextLevelCommands.emplace_back(std::move(pCommand));
}

const dae::Level& dae::LevelComponent::GetLevelInfo() const {
	return m_levelInfo;
}

bool dae::LevelComponent::FlickTile(Tile* tile) const {
	if (m_levelInfo.tileBehavior == "default") {
		if (tile->state == 0) {
			tile->state = 1;
			return true;
		}

		return false;
	}

	if (m_levelInfo.tileBehavior == "increment") {
		if (tile->state < 2) {
			tile->state += 1;
		}

		return true;
	}

	if (m_levelInfo.tileBehavior == "revert") {
		if (tile->state == 0) {
			tile->state = 1;
			return true;
		} else {
			tile->state = 0;
		}

		return false;
	}

	std::cerr << "Unknown tile behaviour: " << m_levelInfo.tileBehavior << std::endl;
	return false;
}

int dae::LevelComponent::GetRequiredTileState() const {
	return m_levelInfo.requiredTileState;
}

dae::Subject& dae::LevelComponent::GetSubject() {
	return m_Subject;
}

dae::RhombilleGridComponent* dae::LevelComponent::GetRhombilleGrid() {
	return m_pRhombilleGrid;
}

dae::RhombilleGridAnimationComponent* dae::LevelComponent::GetRhombileGridAnimationComponent() {
	return m_pRhombilleGridAnimationComponent;
}

dae::EnemySpawnerComponent* dae::LevelComponent::GetEnemySpawner() {
	return m_pEnemySpawner;
}

void dae::LevelComponent::Update(float deltaTime) {
	if (!m_hasUpdated) {
		DestroySpinningDiscs();
		m_totalSpinningDiscs = m_levelInfo.rounds[m_round].discs;

		SpawnSpinningDiscs();
		m_hasUpdated = true;
	}

	if (!m_inResetAnimation) {
		return;
	}

	if (m_resetTimeLeft <= 0.f) {
		m_inResetAnimation = false;

		for (auto player : m_Players) {
			player->Reset(); // Reset the player component
		}

		if (m_pEnemySpawner != nullptr) {
			m_pEnemySpawner->KillAllEnemies();
			const auto& enemies = m_levelInfo.rounds[m_round].enemies;
			m_pEnemySpawner->PrepareEnemies(enemies);
		}

		m_pRhombilleGrid->SetVariant(GetTileVariant());
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
	for (size_t discIndex{ m_spinningDiscs.size() }; discIndex < static_cast<size_t>(m_totalSpinningDiscs); discIndex++) {
		// Compute position for disc:
		int row{};
		int col{};
		bool exists{};
		do {
			row = m_pRhombilleGrid->GetRandomRow();
			col = rand() % 2 == 0 ? -1 : row + 1;

			for (const auto& disc : m_spinningDiscs) {
				exists = disc->GetRow() == row && disc->GetCol() == col;
			}
		} while (exists);

		auto discObject{ std::make_unique<GameObject>(Transform{ -999.f, -999.f })};
		auto pSpriteComponent{ discObject->AddComponent<SpriteComponent>("Disk Spritesheet.png", 16, 10, 2.f) };
		auto pDiscComponent{ discObject->AddComponent<SpinningDiscComponent>(m_pRhombilleGrid, row, col) };
		m_spinningDiscs.emplace_back(pDiscComponent);
		pDiscComponent->GetSubject().AddObserver(Qbert::GetInstance().GetSoundObserver());

		int variant{ m_pRhombilleGrid->GetVariant() };
		pSpriteComponent->AddState(make_sdbm_hash("idle"), SpriteComponent::State{ variant * 5, 0, 4, 10 });

		pSpriteComponent->SetState(make_sdbm_hash("idle"));

		SceneManager::GetInstance().GetActiveScene()->Add(std::move(discObject));
	}
}

void dae::LevelComponent::DestroySpinningDiscs() {
	for (auto disc : m_spinningDiscs) {
		disc->GetOwner().Destroy();
	}

	m_spinningDiscs.clear();
}
