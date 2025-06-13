#include "EnemySpawnerComponent.h"
#include "hash.h"
#include "SpriteComponent.h"
#include "CoilyComponent.h"
#include "RhombilleGridComponent.h"
#include "CoilyStateBall.h"
#include "SceneManager.h"
#include "GridNavigationComponent.h"
#include "SlickAndSlamObserver.h"
#include "UggAndWrongwayObserver.h"
#include "SlickAndSlamComponent.h"
#include "UggAndWrongwayComponent.h"
#include "LevelComponent.h"
#include "Scene.h"
#include <iostream>

dae::EnemySpawnerComponent::EnemySpawnerComponent(GameObject& pOwner, GridMovementComponent* pTargetComponent, LevelComponent* pLevelComponent) 
	: BaseComponent(pOwner), m_pTargetComponent(pTargetComponent), m_pLevelComponent(pLevelComponent) {
	m_pRhombilleGridComponent = GetOwner().GetComponent<RhombilleGridComponent>();
	m_levelInfo = m_pLevelComponent->GetLevelInfo();
}

void dae::EnemySpawnerComponent::KillAllEnemies() {
	for (auto& enemy : m_spawnedEnemies) {
		enemy->Destroy();
	}
}

void dae::EnemySpawnerComponent::PrepareEnemies(const std::vector<Enemy>& enemies) {
	m_enemiesToSpawn.clear();
	for (const auto& enemy : enemies) {
		for (int i = 0; i < enemy.count; ++i) {
			m_enemiesToSpawn.push_back(enemy); // Copy each instance
		}
	}

	m_currentEnemyIndex = 0;
	if (!m_enemiesToSpawn.empty()) {
		m_nextEnemyDelay = m_enemiesToSpawn[0].delay;
	}
}

void dae::EnemySpawnerComponent::Update(float deltaTime) {
	if (m_pLevelComponent->LevelPaused() || m_currentEnemyIndex >= m_enemiesToSpawn.size())
		return;

	m_nextEnemyDelay -= deltaTime;
	if (m_nextEnemyDelay <= 0.f) {
		const auto& enemy = m_enemiesToSpawn[m_currentEnemyIndex];
		SpawnEnemyOfType(enemy.type);
		++m_currentEnemyIndex;

		if (m_currentEnemyIndex < m_enemiesToSpawn.size()) {
			m_nextEnemyDelay = m_enemiesToSpawn[m_currentEnemyIndex].delay;
		}
	}
}

void dae::EnemySpawnerComponent::PostUpdate() {
	// Remove any potentially destroyed enemies from the list of spawned game enemies
	m_spawnedEnemies.erase(
		std::remove_if(m_spawnedEnemies.begin(), m_spawnedEnemies.end(),
			[](const GameObject* enemy) {
				return enemy->IsDestroyed();
			}), m_spawnedEnemies.end());
}

void dae::EnemySpawnerComponent::SpawnEnemyOfType(const std::string& type) {
	if (type == "Coily") {
		m_spawnedEnemies.emplace_back(SpawnCoily());
	} else if (type == "UggAndWrongway") {
		m_spawnedEnemies.emplace_back(SpawnUggOrWrongWay());
	} else if (type == "SlickAndSam") {
		m_spawnedEnemies.emplace_back(SpawnSlickOrSlam());
	} else {
		std::cout << "Enemy of type: " << type << " does not exist!";
	}
}

dae::GameObject* dae::EnemySpawnerComponent::SpawnCoily() {
	auto coilyObject{ std::make_unique<GameObject>(Transform{ -999.f, -999.f }) };
	auto coilySprite{ coilyObject->AddComponent<SpriteComponent>("Coily Spritesheet.png", 16, 32, 2.f) };
	auto movementComponent{ coilyObject->AddComponent<GridMovementComponent>(m_pRhombilleGridComponent, m_pLevelComponent, 0, 0, 0.5f) };
	coilyObject->AddComponent<GridNavigationComponent>(0.5f);
	auto coilyComponent{ coilyObject->AddComponent<CoilyComponent>(m_pTargetComponent, m_pLevelComponent) };

	movementComponent->SetOffsetX(32 + 16);
	movementComponent->SetOffsetY(32);

	coilySprite->AddState(make_sdbm_hash("ball_idle"), SpriteComponent::State{ 0, 0, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("ball_jump"), SpriteComponent::State{ 1, 0, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("idle_up"), SpriteComponent::State{ 2, 0, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("jump_up"), SpriteComponent::State{ 3, 0, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("idle_left"), SpriteComponent::State{ 4, 0, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("jump_left"), SpriteComponent::State{ 5, 0, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("idle_right"), SpriteComponent::State{ 6, 0, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("jump_right"), SpriteComponent::State{ 7, 0, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("idle_down"), SpriteComponent::State{ 8, 0, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("jump_down"), SpriteComponent::State{ 9, 0, 1, 0 });


	coilyComponent->SetState(std::make_shared<CoilyStateBall>(coilyComponent, m_pTargetComponent));

	auto eObj{ coilyObject.get() };
	SceneManager::GetInstance().GetActiveScene()->Add(std::move(coilyObject));
	return eObj;
}

dae::GameObject* dae::EnemySpawnerComponent::SpawnUggOrWrongWay() {
	auto enemyObject{ std::make_unique<GameObject>(Transform{ -999.f, -999.f }) };

	// Spawn position
	int row{ m_pRhombilleGridComponent->GetRows() -1 };
	int col{ (rand() % 2) * row};

	auto pSpriteComponent{ enemyObject->AddComponent<SpriteComponent>("Ugg Wrongway Spritesheet.png", 16, 16, 2.f) };
	auto pMovementComponent{ enemyObject->AddComponent<GridMovementComponent>(m_pRhombilleGridComponent, m_pLevelComponent, row, col, 0.5f) };
	auto pNavigationComponent{ enemyObject->AddComponent<GridNavigationComponent>(0.5f) };
	enemyObject->AddComponent<UggAndWrongwayComponent>(m_pTargetComponent, m_pLevelComponent);

	pNavigationComponent->SetTarget(0, 0);

	pMovementComponent->SetOffsetX(16);
	pMovementComponent->SetOffsetY(16);

	int variant{ rand() % 2 };

	pSpriteComponent->AddState(make_sdbm_hash("roll1"), SpriteComponent::State{ 0, variant, 1, 0 });
	pSpriteComponent->AddState(make_sdbm_hash("roll2"), SpriteComponent::State{ 1, variant, 1, 0 });
	pSpriteComponent->AddState(make_sdbm_hash("roll3"), SpriteComponent::State{ 2, variant, 1, 0 });
	pSpriteComponent->AddState(make_sdbm_hash("roll4"), SpriteComponent::State{ 3, variant, 1, 0 });

	pSpriteComponent->SetState(make_sdbm_hash("roll1"));

	pMovementComponent->GetSubject().AddObserver(std::make_shared<UggAndWrongwayObserver>(pSpriteComponent));

	auto eObj{ enemyObject.get() };
	SceneManager::GetInstance().GetActiveScene()->Add(std::move(enemyObject));
	return eObj;
}

dae::GameObject* dae::EnemySpawnerComponent::SpawnSlickOrSlam() {
	auto enemyObject{ std::make_unique<GameObject>(Transform{ -999.f, -999.f }) };

	auto pSpriteComponent{ enemyObject->AddComponent<SpriteComponent>("Slick Sam Spritesheet.png", 12, 16, 2.f) };
	auto pMovementComponent{ enemyObject->AddComponent<GridMovementComponent>(m_pRhombilleGridComponent, m_pLevelComponent, 0, 0, 0.5f) };
	auto pNavigationComponent{ enemyObject->AddComponent<GridNavigationComponent>(0.5f) };
	enemyObject->AddComponent<SlickAndSlamComponent>(m_pTargetComponent, m_pLevelComponent);

	int row{ m_pRhombilleGridComponent->GetRows() };
	int col{ m_pRhombilleGridComponent->GetRandomCol(row) };

	pNavigationComponent->SetTarget(row, col);

	pMovementComponent->SetOffsetX(12);
	pMovementComponent->SetOffsetY(16);

	int variant{ rand() % 2 };

	pSpriteComponent->AddState(make_sdbm_hash("left"), SpriteComponent::State{ 0, variant, 1, 0 });
	pSpriteComponent->AddState(make_sdbm_hash("right"), SpriteComponent::State{ 1, variant, 1, 0 });

	pSpriteComponent->SetState(make_sdbm_hash("left"));

	pMovementComponent->GetSubject().AddObserver(std::make_shared<SlickAndSlamObserver>(pSpriteComponent));

	auto eObj{ enemyObject.get() };
	SceneManager::GetInstance().GetActiveScene()->Add(std::move(enemyObject));
	return eObj;
}
