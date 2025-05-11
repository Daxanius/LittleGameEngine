#include "EnemySpawnerComponent.h"
#include "hash.h"
#include "SpriteComponent.h"
#include "CoilyComponent.h"
#include "RhombilleGridComponent.h"
#include "CoilyStateBall.h"
#include "SceneManager.h"
#include "CoilyMovementObserver.h"
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
	int row{};
	int col{};

	m_pRhombilleGridComponent->GetRandomTile(row, col);

	auto coilyObject{ std::make_shared<GameObject>(Transform{ 0.f, 0.f }) };
	auto coilySprite{ coilyObject->AddComponent<SpriteComponent>("Coily Spritesheet.png", 17, 17, 2.f) };
	auto coilyMovement{ coilyObject->AddComponent<GridMovementComponent>(m_pRhombilleGridComponent, row, col, 0.5f) };
	auto coilyComponent{ coilyObject->AddComponent<CoilyComponent>() };

	coilySprite->AddState(make_sdbm_hash("up"), SpriteComponent::State{ 0, 0, 0 });
	coilySprite->AddState(make_sdbm_hash("down"), SpriteComponent::State{ 3, 0, 0 });
	coilySprite->AddState(make_sdbm_hash("left"), SpriteComponent::State{ 1, 0, 0 });
	coilySprite->AddState(make_sdbm_hash("right"), SpriteComponent::State{ 2, 0, 0 });
	coilySprite->SetState(make_sdbm_hash("right"));

	coilyComponent->SetState(std::make_shared<CoilyStateBall>(coilyComponent, m_pTargetComponent));
	coilyMovement->GetSubject().AddObserver(std::static_pointer_cast<Observer>(std::make_shared<CoilyMovementObserver>(coilyComponent, m_pTargetComponent)));


	m_pRhombilleGridComponent->GetTile(coilyMovement->GetRow(), coilyMovement->GetCol())->state = -1;
	SceneManager::GetInstance().GetActiveScene()->Add(coilyObject);

	coilyObject->SetParent(&GetOwner(), true);
}
