#pragma once
#include "BaseComponent.h"
#include "RhombilleGridComponent.h"
#include "GridMovementComponent.h"
#include "Level.h"

namespace dae {
	class LevelComponent;

	class EnemySpawnerComponent : public BaseComponent {
	public:
		EnemySpawnerComponent(GameObject& pOwner, GridMovementComponent* pTargetComponent, LevelComponent* pLevelComponent);

		void KillAllEnemies();

		void PrepareEnemies(const std::vector<Enemy>& enemies);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override;
		void Render() override {};
	private:
		std::vector<Enemy> m_enemiesToSpawn;
		size_t m_currentEnemyIndex{ 0 };
		float m_nextEnemyDelay{ 0.f };

		void SpawnEnemyOfType(const std::string& type);

		GameObject* SpawnCoily();
		GameObject* SpawnUggOrWrongWay();
		GameObject* SpawnSlickOrSlam();

		RhombilleGridComponent* m_pRhombilleGridComponent{};
		GridMovementComponent* m_pTargetComponent{};
		LevelComponent* m_pLevelComponent{};

		Level m_levelInfo{};

		std::vector<GameObject*> m_spawnedEnemies{};
	};
}

