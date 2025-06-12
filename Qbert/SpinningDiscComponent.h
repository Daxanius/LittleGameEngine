#pragma once
#include <BaseComponent.h>
#include "RhombilleGridComponent.h"
#include "SpriteComponent.h"
#include "PlayerComponent.h"

namespace dae {
	class SpinningDiscComponent : public BaseComponent {
	public:
		SpinningDiscComponent(GameObject& pOwner, RhombilleGridComponent* pRhombileGridComponent, int row, int col, float travelTime = 2.f);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};

		int GetRow() const;
		int GetCol() const;

		bool TransportPlayer(PlayerComponent* pPlayerComponent);

		bool IsTransportingPlayer() const;
	private:
		glm::vec2 m_startPosition{};
		glm::vec2 m_goalPosition{};

		float m_travelTime{};
		float m_elapsedTime{};

		int m_row;
		int m_col;

		PlayerComponent* m_pCurrentPlayer{ nullptr };
		SpriteComponent* m_pSpriteComponent;
		RhombilleGridComponent* m_pRhombileGridComponent;
	};
}

