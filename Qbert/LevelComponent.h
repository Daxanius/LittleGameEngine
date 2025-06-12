#pragma once
#include <BaseComponent.h>
#include "Subject.h"
#include <vector>

namespace dae {
	class PlayerComponent;
	class SpinningDiscComponent;
	class Command;
	class RhombilleGridComponent;
	class EnemySpawnerComponent;

	class LevelComponent : public BaseComponent {
	public:
		LevelComponent(GameObject& pOwner, float resetTime);

		void NextRound();

		int GetRound() const;

		// Pause an unpause are used for animations
		void PauseLevel();
		void UnpauseLevel();

		bool CheckSpinningDiscs();

		void ResetLevel(bool resetState = false);

		bool LevelPaused() const;
		bool InResetAnimation() const;

		void RegisterPlayer(PlayerComponent* pPlayer);
		void RegisterSpawner(EnemySpawnerComponent* pSpawner);

		void AddGameOverCommand(std::unique_ptr<Command>&& pCommand);

		Subject& GetSubject();

		RhombilleGridComponent& GetRhombilleGrid();
		EnemySpawnerComponent& GetEnemySpawner();

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override;
		void Render() override {};

		const std::vector<PlayerComponent*>& GetPlayers() const;

		static constexpr int ROUNDS_PER_LEVEL{ 4 };
	private:
		void SpawnSpinningDiscs();

		float m_resetTime{};
		float m_resetTimeLeft{};

		int m_totalSpinningDiscs{ 1 };

		// Keeping track of them rounds
		int m_Round{};

		bool m_Paused{};

		bool m_InResetAnimation{};
		bool m_ShouldResetState{};
		bool m_HasSpawnedDiscs{};

		Subject m_Subject{};

		RhombilleGridComponent* m_pRhombilleGrid{};
		EnemySpawnerComponent* m_pEnemySpawner{};

		std::vector<PlayerComponent*> m_Players;
		std::vector<SpinningDiscComponent*> m_spinningDiscs;
		std::vector<std::unique_ptr<Command>> m_gameOverCommands;
	};
}
