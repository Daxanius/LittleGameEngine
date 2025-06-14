#pragma once
#include <BaseComponent.h>
#include "GridMovementComponent.h"
#include "GridNavigationComponent.h"
#include "LevelComponent.h"
#include "Subject.h"

namespace dae {
	class UggAndWrongwayComponent final : public BaseComponent {
	public:
		UggAndWrongwayComponent(GameObject& pOwner, LevelComponent* pLevelComponent, bool isUgg);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};

		Subject& GetSubject();

		UggAndWrongwayComponent(const UggAndWrongwayComponent&) = delete;
		UggAndWrongwayComponent& operator=(const UggAndWrongwayComponent&) = delete;
		UggAndWrongwayComponent(UggAndWrongwayComponent&&) = delete;
		UggAndWrongwayComponent& operator=(UggAndWrongwayComponent&&) = delete;
		~UggAndWrongwayComponent() = default;
	private:
		GridMovementComponent* m_pOwnMovementComponent{};
		GridNavigationComponent* m_pNavigationComponent{};
		LevelComponent* m_pLevelComponent{};

		bool m_isUgg{};

		Subject m_subject{};
	};
}
