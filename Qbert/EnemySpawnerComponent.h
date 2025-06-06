#pragma once
#include "BaseComponent.h"
#include "RhombilleGridComponent.h"
#include "GridMovementComponent.h"

namespace dae {
	class LevelComponent;

	class EnemySpawnerComponent : public BaseComponent {
	public:
		EnemySpawnerComponent(GameObject& pOwner, GridMovementComponent* pTargetComponent, LevelComponent* pLevelComponent, float spawnInterval);

		void KillAllEnemies();

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};
	private:
		float m_spawnInterval;
		float m_timeUntilSpawn;

		void SpawnEnemy();

		GameObject* SpawnCoily();

		RhombilleGridComponent* m_pRhombilleGridComponent{};
		GridMovementComponent* m_pTargetComponent{};
		LevelComponent* m_pLevelComponent{};

		std::vector<GameObject*> m_spawnedEnemies{};
	};
}

