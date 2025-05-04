#pragma once
#include <BaseComponent.h>
#include "RhombilleGridComponent.h"

namespace dae {
	class GridMovementComponent : public BaseComponent {
	public:
		GridMovementComponent(GameObject& pOwner, RhombilleGridComponent* pRhombilleGrid, int row = 0, int col = 0);

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
	private:
		RhombilleGridComponent* m_pRhombilleGrid;

		// Grid position
		int m_row{};
		int m_col{};
	};
}
