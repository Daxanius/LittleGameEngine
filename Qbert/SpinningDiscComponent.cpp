#include "SpinningDiscComponent.h"
#include <algorithm>

dae::SpinningDiscComponent::SpinningDiscComponent(GameObject& pOwner, RhombilleGridComponent* pRhombileGridComponent, int row, int col, float travelTime)
 : BaseComponent(pOwner), m_pRhombileGridComponent(pRhombileGridComponent), m_row(row), m_col(col), m_travelTime(travelTime) {
	m_pSpriteComponent = GetComponent<SpriteComponent>();
}

void dae::SpinningDiscComponent::Update(float deltaTime) {
	// If we're not transporting a player, ignore
	if (m_pCurrentPlayer == nullptr) {
		const auto newPosition = m_pRhombileGridComponent->ToWorldPosition(m_row, m_col);
		GetOwner().SetLocalPosition(glm::vec2{ newPosition.x + 8.f, newPosition.y + 5.f });
		return;
	}

	if (m_elapsedTime >= m_travelTime) {
		m_pCurrentPlayer->GetOwner().SetParent(nullptr, true);
		m_pCurrentPlayer->DisableFreeMovement();
		m_pCurrentPlayer->SetInvulnerable(false);
		m_pCurrentPlayer->GetMovementComponent()->MoveToPosition(0, 0);
		m_pCurrentPlayer = nullptr;
		GetOwner().Destroy(); // Destroy the disc game object
		return;
	}

	float progress{ (m_elapsedTime / m_travelTime) };
	progress = std::clamp(progress, 0.f, 1.f);
	const auto newPosition = m_startPosition + (progress * (m_goalPosition - m_startPosition));
	GetOwner().SetLocalPosition(newPosition);
	
	m_elapsedTime += deltaTime;
}

int dae::SpinningDiscComponent::GetRow() const {
	return m_row;
}

int dae::SpinningDiscComponent::GetCol() const {
	return m_col;
}

bool dae::SpinningDiscComponent::TransportPlayer(PlayerComponent* pPlayerComponent) {
	if (m_pCurrentPlayer != nullptr) {
		return false;
	}

	m_pCurrentPlayer = pPlayerComponent;
	m_pCurrentPlayer->EnableFreeMovement();
	m_pCurrentPlayer->SetInvulnerable(true);
	m_pCurrentPlayer->GetOwner().SetParent(&GetOwner(), false);
	m_pCurrentPlayer->GetOwner().SetLocalPosition(glm::vec2{ 2.f, -24.f });
	m_elapsedTime = 0.f;

	m_startPosition = GetOwner().GetWorldTransform().GetPosition();
	m_goalPosition = m_pRhombileGridComponent->ToWorldPosition(0, 0);
	return true;
}

bool dae::SpinningDiscComponent::IsTransportingPlayer() const {
	return m_pCurrentPlayer != nullptr;
}
