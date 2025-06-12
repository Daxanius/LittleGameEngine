#pragma once
#include <BaseComponent.h>
#include "Subject.h"
#include "Level.h"
#include <vector>

namespace dae {
	class PlayerComponent;
	class SpinningDiscComponent;
	class Command;
	class RhombilleGridComponent;
	class EnemySpawnerComponent;

	class LevelComponent : public BaseComponent {
	public:
		LevelComponent(GameObject& pOwner, float resetTime, const Level& levelInfo);

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
		void DestroySpinningDiscs();

		float m_resetTime{};
		float m_resetTimeLeft{};

		int m_totalSpinningDiscs{ 1 };

		// Keeping track of them rounds
		int m_Round{};

		bool m_Paused{};

		bool m_inResetAnimation{};
		bool m_shouldResetState{};
		bool m_hasUpdated{};

		Subject m_Subject{};

		RhombilleGridComponent* m_pRhombilleGrid{};
		EnemySpawnerComponent* m_pEnemySpawner{};

		Level m_levelInfo;

		std::vector<PlayerComponent*> m_Players;
		std::vector<SpinningDiscComponent*> m_spinningDiscs;
		std::vector<std::unique_ptr<Command>> m_gameOverCommands;
	};
}
