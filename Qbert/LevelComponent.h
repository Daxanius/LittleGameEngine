#pragma once
#include <BaseComponent.h>
#include "Subject.h"
#include "RhombilleGridComponent.h"
#include "PlayerComponent.h"
#include "EnemySpawnerComponent.h"

namespace dae {
	class LevelComponent : public BaseComponent {
	public:
		LevelComponent(GameObject& pOwner, float resetTime);

		void NextRound();

		int GetRound() const;
		int GetLevel() const;

		// Pause an unpause are used for animations
		void PauseLevel();
		void UnpauseLevel();

		void ResetLevel(bool resetState = false);

		bool LevelPaused() const;
		bool InResetAnimation() const;

		void RegisterPlayer(PlayerComponent* pPlayer);
		void RegisterSpawner(EnemySpawnerComponent* pSpawner);

		Subject& GetSubject();

		RhombilleGridComponent& GetRhombilleGrid();
		EnemySpawnerComponent& GetEnemySpawner();

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};

		const std::vector<PlayerComponent*>& GetPlayers() const;

		static constexpr int ROUNDS_PER_LEVEL{ 4 };
	private:
		float m_resetTime{};
		float m_resetTimeLeft{};

		// Keeping track of them rounds and levels
		int m_Round{};
		int m_Level{};

		bool m_Paused{};

		bool m_InResetAnimation{};
		bool m_ShouldResetState{};

		Subject m_Subject{};

		RhombilleGridComponent* m_pRhombilleGrid{};
		EnemySpawnerComponent* m_pEnemySpawner{};

		std::vector<PlayerComponent*> m_Players;
	};
}
