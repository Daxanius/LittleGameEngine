#include "GridMovementComponent.h"
#include "LevelComponent.h"
#include "hash.h"

dae::GridMovementComponent::GridMovementComponent(GameObject& pOwner, RhombilleGridComponent* pRhombilleGrid, LevelComponent* pLevelComponent, int row, int col, float jumpDuration) 
	: BaseComponent(pOwner), m_pRhombilleGrid(pRhombilleGrid), m_pLevelComponent(pLevelComponent), m_row(row), m_col(col), m_jumpDuration(jumpDuration) {
}

void dae::GridMovementComponent::Update(float deltaTime) {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	// If not jumping, just snap to position (e.g. at start)
	if (!m_isJumping) {
		glm::vec2 standingPosition{ ToStandingPosition(m_row, m_col) };
		GetOwner().SetLocalTransform(Transform{ standingPosition.x, standingPosition.y });
		return;
	}

	m_elapsedJumpTime += deltaTime;
	float t = glm::clamp(m_elapsedJumpTime / m_jumpDuration, 0.f, 1.f);

	// Interpolate position
	glm::vec2 pos = glm::mix(m_startPos, m_endPos, t);

	// Jump arc
	float arc = -4 * JUMP_HEIGHT * (t - 0.5f) * (t - 0.5f) + JUMP_HEIGHT;
	pos.y -= arc;

	GetOwner().SetLocalTransform(pos);
	if (t >= 1.f) {
		m_isJumping = false;

		m_prevRow = m_row;
		m_prevCol = m_col;
		m_row = m_targetRow;
		m_col = m_targetCol;

		// Arrive
		Event event{ make_sdbm_hash("arrive") };
		event.data = ArriveEventData{
			m_row,
			m_col
		};
		m_subject.Notify(event);
	}
}

int dae::GridMovementComponent::GetRow() const {
	return m_row;
}

int dae::GridMovementComponent::GetCol() const {
	return m_col;
}

int dae::GridMovementComponent::GetPrevRow() const {
	return m_prevRow;
}

int dae::GridMovementComponent::GetPrevCol() const {
	return m_prevCol;
}

int dae::GridMovementComponent::GetTargetRow() const {
	return m_targetRow;
}

int dae::GridMovementComponent::GetTargetCol() const {
	return m_targetCol;
}

void dae::GridMovementComponent::GoToPrevPosition() {
	m_isJumping = false;
	m_row = m_prevRow;
	m_col = m_prevCol;

	auto pos = ToStandingPosition(m_row, m_col);
	GetOwner().SetLocalTransform(pos);
}

void dae::GridMovementComponent::ResetPosition() {
	m_isJumping = false;
	m_row = 0;
	m_col = 0;
	m_prevRow = 0;
	m_prevCol = 0;

	auto pos = ToStandingPosition(m_row, m_col);
	GetOwner().SetLocalTransform(pos);
}

void dae::GridMovementComponent::MoveUp() {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	if (StartJump(m_row - 1, m_col)) {
		Event event{ make_sdbm_hash("move_up") };
		m_subject.Notify(event);
	}
}

void dae::GridMovementComponent::MoveDown() {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	if (StartJump(m_row + 1, m_col)) {
		Event event{ make_sdbm_hash("move_down") };
		m_subject.Notify(event);
	}
}

void dae::GridMovementComponent::MoveLeft() {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	if (StartJump(m_row - 1, m_col - 1)) {
		Event event{ make_sdbm_hash("move_left") };
		m_subject.Notify(event);
	}
}

void dae::GridMovementComponent::MoveRight() {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	if (StartJump(m_row + 1, m_col + 1)) {
		Event event{ make_sdbm_hash("move_right") };
		m_subject.Notify(event);
	}
}

void dae::GridMovementComponent::MoveUpLeft() {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	if (StartJump(m_row - 1, m_col - 1)) {
		Event event{ make_sdbm_hash("move_up_left") };
		m_subject.Notify(event);
	}
}

void dae::GridMovementComponent::MoveUpRight() {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	if (StartJump(m_row - 1, m_col)) {
		Event event{ make_sdbm_hash("move_up_right") };
		m_subject.Notify(event);
	}
}

void dae::GridMovementComponent::MoveDownLeft() {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	if (StartJump(m_row + 1, m_col)) {
		Event event{ make_sdbm_hash("move_down_left") };
		m_subject.Notify(event);
	}
}

void dae::GridMovementComponent::MoveDownRight() {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	if (StartJump(m_row + 1, m_col + 1)) {
		Event event{ make_sdbm_hash("move_down_right") };
		m_subject.Notify(event);
	}
}

void dae::GridMovementComponent::SetOffsetX(int width) {
	if (width < 0) {
		return;
	}

	m_offsetX = width;
}

void dae::GridMovementComponent::SetOffsetY(int height) {
	if (height < 0) {
		return;
	}

	m_offsetY = height;
}

bool dae::GridMovementComponent::IsJumping() const {
    return m_isJumping;
}

dae::Subject& dae::GridMovementComponent::GetSubject() {
	return m_subject;
}

dae::RhombilleGridComponent* dae::GridMovementComponent::GetRhombilleGrid() const {
	return m_pRhombilleGrid;
}

glm::vec2 dae::GridMovementComponent::ToStandingPosition(int row, int col) const {
	glm::vec2 cubePos = m_pRhombilleGrid->ToWorldPosition(row, col);

	const float tileWidth = m_pRhombilleGrid->GetTileWidth() * m_pRhombilleGrid->GetScale();
	const float tileHeight = m_pRhombilleGrid->GetTileHeight() * m_pRhombilleGrid->GetScale();

	cubePos.x += (tileWidth * 0.5f - m_offsetX);
	cubePos.y -= (tileHeight * 0.5f) - m_offsetY;
	return cubePos;
}

bool dae::GridMovementComponent::StartJump(int newRow, int newCol) {
	if (m_isJumping) {
		return false;
	}

	m_isJumping = true;
	m_elapsedJumpTime = 0.f;

	m_startPos = ToStandingPosition(m_row, m_col);
	m_endPos = ToStandingPosition(newRow, newCol);

	m_targetRow = newRow;
	m_targetCol = newCol;

	return true;
}
