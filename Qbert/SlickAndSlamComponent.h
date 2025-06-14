#pragma once
#include <BaseComponent.h>
#include "GridMovementComponent.h"
#include "GridNavigationComponent.h"
#include "LevelComponent.h"
#include "Subject.h"

namespace dae {
	class SlickAndSlamComponent final : public BaseComponent {
	public:
		SlickAndSlamComponent(GameObject& pOwner, LevelComponent* pLevelComponent);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};

		Subject& GetSubject();


		SlickAndSlamComponent(const SlickAndSlamComponent&) = delete;
		SlickAndSlamComponent& operator=(const SlickAndSlamComponent&) = delete;
		SlickAndSlamComponent(SlickAndSlamComponent&&) = delete;
		SlickAndSlamComponent& operator=(SlickAndSlamComponent&&) = delete;
		~SlickAndSlamComponent() = default;
	private:
		GridMovementComponent* m_pOwnMovementComponent{};
		GridNavigationComponent* m_pNavigationComponent{};
		LevelComponent* m_pLevelComponent{};

		Subject m_subject{};
	};
}

