#include "GridMovementComponent.h"

dae::GridMovementComponent::GridMovementComponent(GameObject& pOwner, RhombilleGridComponent* pRhombilleGrid, int row, int col) : BaseComponent(pOwner), m_pRhombilleGrid(pRhombilleGrid), m_row(row), m_col(col) {
}

void dae::GridMovementComponent::Update(float) {
	glm::vec2 cubePos = m_pRhombilleGrid->ToWorldPosition(m_row, m_col);

	const float spriteWidth = 16.f;
	const float spriteHeight = 16.f;

	const float tileWidth = m_pRhombilleGrid->GetTileWidth() * m_pRhombilleGrid->GetScale();
	const float tileHeight = m_pRhombilleGrid->GetTileHeight() * m_pRhombilleGrid->GetScale();

	cubePos.x += (tileWidth * 0.5f - spriteWidth);

	cubePos.y -= (tileHeight * 0.5f) - spriteHeight;

	GetOwner().SetLocalTransform(Transform{ cubePos.x, cubePos.y });
}

int dae::GridMovementComponent::GetRow() const {
	return m_row;
}

int dae::GridMovementComponent::GetCol() const {
	return m_col;
}

void dae::GridMovementComponent::MoveUp() {
	m_row -= 1;
}

void dae::GridMovementComponent::MoveDown() {
	m_row += 1;
}

void dae::GridMovementComponent::MoveLeft() {
	m_row -= 1;
	m_col -= 1;
}

void dae::GridMovementComponent::MoveRight() {
	m_row += 1;
	m_col += 1;
}
