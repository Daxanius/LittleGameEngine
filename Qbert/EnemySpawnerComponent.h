#pragma once
#include "BaseComponent.h"
#include "RhombilleGridComponent.h"
#include "GridMovementComponent.h"

namespace dae {
	class EnemySpawnerComponent : public BaseComponent {
	public:
		EnemySpawnerComponent(GameObject& pOwner, GridMovementComponent* pTargetComponent, float spawnInterval);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};
	private:
		float m_spawnInterval;
		float m_timeUntilSpawn;

		void SpawnEnemy();

		void SpawnCoily();

		RhombilleGridComponent* m_pRhombilleGridComponent{};
		GridMovementComponent* m_pTargetComponent{};
	};
}

