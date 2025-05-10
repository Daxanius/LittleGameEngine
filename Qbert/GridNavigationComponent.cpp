#include "GridNavigationComponent.h"

dae::GridNavigationComponent::GridNavigationComponent(GameObject& pOwner, float jumpCooldown)
	: BaseComponent(pOwner), m_jumpCooldown(jumpCooldown), m_timeSinceLastJump(jumpCooldown) {
	m_pMovementComponent = pOwner.GetComponent<GridMovementComponent>();
	assert(m_pMovementComponent != nullptr);
}

void dae::GridNavigationComponent::Update(float deltaTime) {
	if (!m_pMovementComponent) {
		return;
	}

	if (m_pMovementComponent->IsJumping()) {
		m_timeSinceLastJump = 0.f;
		return;
	}

	m_timeSinceLastJump += deltaTime;

	if (m_timeSinceLastJump < m_jumpCooldown) {
		return;
	}

	int curRow = m_pMovementComponent->GetRow();
	int curCol = m_pMovementComponent->GetCol();

	if (curRow == m_targetRow && curCol == m_targetCol) {
		return;
	}

	// Choose next direction toward target
	if (m_targetRow < curRow && m_targetCol == curCol) {
		m_pMovementComponent->MoveUp();
	} else if (m_targetRow > curRow && m_targetCol == curCol) {
		m_pMovementComponent->MoveDown();
	} else if (m_targetRow < curRow && m_targetCol < curCol) {
		m_pMovementComponent->MoveLeft();
	} else if (m_targetRow > curRow && m_targetCol > curCol) {
		m_pMovementComponent->MoveRight();
	}

	m_timeSinceLastJump = 0.f;
}

void dae::GridNavigationComponent::SetTarget(int row, int col) {
	m_targetRow = row;
	m_targetCol = col;
}

bool dae::GridNavigationComponent::HasArrived() const {
	if (!m_pMovementComponent) return true;
	return !m_pMovementComponent->IsJumping() &&
		m_pMovementComponent->GetRow() == m_targetRow &&
		m_pMovementComponent->GetCol() == m_targetCol;
}