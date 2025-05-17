#include "GridNavigationComponent.h"

dae::GridNavigationComponent::GridNavigationComponent(GameObject& pOwner, float jumpCooldown)
	: BaseComponent(pOwner), m_jumpCooldown(jumpCooldown), m_timeSinceLastJump(jumpCooldown), m_enabled(true) {
	m_pMovementComponent = pOwner.GetComponent<GridMovementComponent>();
	assert(m_pMovementComponent != nullptr);
}

void dae::GridNavigationComponent::Update(float deltaTime) {
	if (!m_pMovementComponent || !m_enabled) {
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

	int dRow = m_targetRow - curRow;
	int dCol = m_targetCol - curCol;

	// Determine the next move based on the difference in row and column
	if (dRow < 0) {
		if (dCol < 0) {
			m_pMovementComponent->MoveUpLeft();
		} else if (dCol > 0) {
			m_pMovementComponent->MoveUpRight();
		} else {
			m_pMovementComponent->MoveUp();
		}
	} else if (dRow > 0) {
		if (dCol < 0) {
			m_pMovementComponent->MoveDownLeft();
		} else if (dCol > 0) {
			m_pMovementComponent->MoveDownRight();
		} else {
			m_pMovementComponent->MoveDown();
		}
	} else {
		if (dCol < 0) {
			m_pMovementComponent->MoveLeft();
		} else if (dCol > 0) {
			m_pMovementComponent->MoveRight();
		}
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

void dae::GridNavigationComponent::Enable() {
	m_enabled = true;
	m_timeSinceLastJump = m_jumpCooldown;
}

void dae::GridNavigationComponent::Disable() {
	m_enabled = false;
	m_timeSinceLastJump = m_jumpCooldown;
}

bool dae::GridNavigationComponent::IsEnabled() const {
	return m_enabled;
}
