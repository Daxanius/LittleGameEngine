#pragma once
#include <BaseComponent.h>
#include "RhombilleGridComponent.h"
#include "Subject.h"

namespace dae {
	class GridMovementComponent : public BaseComponent {
	public:
		GridMovementComponent(GameObject& pOwner, RhombilleGridComponent* pRhombilleGrid, int row = 0, int col = 0);

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

		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();

		Subject& GetSubject();
	private:
		static constexpr float JUMP_HEIGHT{ 10.f };

		RhombilleGridComponent* m_pRhombilleGrid;

		// Grid position
		int m_row{};
		int m_col{};

		// Jump animation
		bool m_isJumping{ false };
		float m_jumpDuration{ 0.2f };
		float m_elapsedJumpTime{ 0.f };

		glm::vec2 m_startPos{};
		glm::vec2 m_endPos{};

		int m_targetRow{};
		int m_targetCol{};

		glm::vec2 ToStandingPosition(int row, int col) const;
		bool StartJump(int newRow, int newCol);

		Subject m_subject{};
	};
}
