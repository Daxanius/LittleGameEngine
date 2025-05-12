#include "EnemySpawnerComponent.h"
#include "hash.h"
#include "SpriteComponent.h"
#include "CoilyComponent.h"
#include "RhombilleGridComponent.h"
#include "CoilyStateBall.h"
#include "SceneManager.h"
#include "GridNavigationComponent.h"
#include "Scene.h"

dae::EnemySpawnerComponent::EnemySpawnerComponent(GameObject& pOwner, GridMovementComponent* pTargetComponent, float spawnInterval) 
	: BaseComponent(pOwner), m_pTargetComponent(pTargetComponent), m_spawnInterval(spawnInterval), m_timeUntilSpawn(m_spawnInterval) {
	m_pRhombilleGridComponent = GetOwner().GetComponent<RhombilleGridComponent>();
}

void dae::EnemySpawnerComponent::Update(float deltaTime) {
	m_timeUntilSpawn -= deltaTime;
	if (m_timeUntilSpawn <= 0.f) {
		SpawnEnemy();
		m_timeUntilSpawn = m_spawnInterval;
	}
}

void dae::EnemySpawnerComponent::SpawnEnemy() {
	SpawnCoily();
}

void dae::EnemySpawnerComponent::SpawnCoily() {
	auto coilyObject{ std::make_shared<GameObject>(Transform{ 0.f, 0.f }) };
	auto coilySprite{ coilyObject->AddComponent<SpriteComponent>("Coily Spritesheet.png", 16, 32, 2.f) };
	auto movementComponent{ coilyObject->AddComponent<GridMovementComponent>(m_pRhombilleGridComponent, 0, 0, 0.5f) };
	coilyObject->AddComponent<GridNavigationComponent>(0.5f);
	auto coilyComponent{ coilyObject->AddComponent<CoilyComponent>() };

	movementComponent->SetOffsetX(32 + 16);
	movementComponent->SetOffsetY(32);

	coilySprite->AddState(make_sdbm_hash("ball_idle"), SpriteComponent::State{ 0, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("ball_jump"), SpriteComponent::State{ 1, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("idle_up"), SpriteComponent::State{ 2, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("jump_up"), SpriteComponent::State{ 3, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("idle_left"), SpriteComponent::State{ 4, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("jump_left"), SpriteComponent::State{ 5, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("idle_right"), SpriteComponent::State{ 6, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("jump_right"), SpriteComponent::State{ 7, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("idle_down"), SpriteComponent::State{ 8, 1, 0 });
	coilySprite->AddState(make_sdbm_hash("jump_down"), SpriteComponent::State{ 9, 1, 0 });


	coilyComponent->SetState(std::make_shared<CoilyStateBall>(coilyComponent, m_pTargetComponent));

	SceneManager::GetInstance().GetActiveScene()->Add(coilyObject);
}
