#pragma once
#include <BaseComponent.h>
#include "GameObject.h"
#include "GridMovementComponent.h"
#include "SpriteComponent.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "Command.h"
#include <memory>

namespace dae {
	class PlayerComponent final : public BaseComponent {
	public:
		PlayerComponent(GameObject& pOwner);

		void ShowTextBalloon();
		void HideTextBalloon();

		SpriteComponent* GetSpriteComponent();
		GridMovementComponent* GetMovementComponent();
		LivesComponent* GetLivesComponent();
		ScoreComponent* GetScoreComponent();

		void AddGameOverCommand(std::unique_ptr<Command> pCommand);

		void Reset(bool resetPosition);

		void Kill(bool shouldGoBack);
		
		bool HasDied() const;

		bool IsInvulnerable() const;
		void SetInvulnerable(bool value);

		void EnableFreeMovement();
		void DisableFreeMovement();

		void FixedUpdate() override {};
		void Update(float) override {};
		void PostUpdate() override {};
		void Render() override {};


		PlayerComponent(const PlayerComponent&) = delete;
		PlayerComponent& operator=(const PlayerComponent&) = delete;
		PlayerComponent(PlayerComponent&&) = delete;
		PlayerComponent& operator=(PlayerComponent&&) = delete;
		~PlayerComponent() = default;
	private:
		GridMovementComponent* m_pGridMovementComponent{};
		SpriteComponent* m_pSpriteComponent{};
		LivesComponent* m_pLivesComponent{};
		ScoreComponent* m_pScoreComponent{};
		GameObject* m_pTextBalloonGo{};

		bool m_died{};
		bool m_shouldGoBack{};

		int m_pStartRow{};
		int m_pStartCol{};

		std::vector<std::unique_ptr<Command>> m_gameOverCommands;
	};
}
