#pragma once
#include <BaseComponent.h>
#include "RhombilleGridComponent.h"
#include "Subject.h"

namespace dae {
	class LevelComponent;

	class GridMovementComponent : public BaseComponent {
	public:
		GridMovementComponent(GameObject& pOwner, RhombilleGridComponent* pRhombilleGrid, LevelComponent* pLevelComponent, int row = 0, int col = 0, float jumpDuration = 0.2f);

		struct ArriveEventData {
			int row;
			int col;
		};

		void FixedUpdate() override {};
		void PostUpdate() override {};
		void Render() override {};
		void Update(float) override;

		int GetRow() const;
		int GetCol() const;

		int GetPrevRow() const;
		int GetPrevCol() const;

		int GetTargetRow() const;
		int GetTargetCol() const;

		void GoToPrevPosition();
		void ResetPosition();

		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();

		// "Diagonal" movement
		void MoveUpLeft();
		void MoveUpRight();
		void MoveDownLeft();
		void MoveDownRight();

		void SetOffsetX(int width);
		void SetOffsetY(int height);

		void SetPosition(int row, int col);

		bool IsJumping() const;

		Subject& GetSubject();

		RhombilleGridComponent* GetRhombilleGrid() const;
	private:
		static constexpr float JUMP_HEIGHT{ 10.f };

		RhombilleGridComponent* m_pRhombilleGrid;
		LevelComponent* m_pLevelComponent;

		// Grid position
		int m_row{};
		int m_col{};

		// Previous grid position
		int m_prevRow{};
		int m_prevCol{};

		// Jump animation
		bool m_isJumping{ false };
		float m_jumpDuration{ 0.2f };
		float m_elapsedJumpTime{ 0.f };

		glm::vec2 m_startPos{};
		glm::vec2 m_endPos{};

		int m_targetRow{};
		int m_targetCol{};

		int m_offsetX{ 16 };
		int m_offsetY{ 16 };

		glm::vec2 ToStandingPosition(int row, int col) const;
		bool StartJump(int newRow, int newCol);

		Subject m_subject{};
	};
}
