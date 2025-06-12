#pragma once
#include "SelectionMenuComponent.h"
#include "Scene.h"
#include <memory>

namespace dae {
	class MenuScene final : public Scene {
	public:
		MenuScene();

		void OnSetup() override;
		void OnEnter() override;

		MenuScene(const MenuScene&) = delete;
		MenuScene& operator=(const MenuScene&) = delete;
		MenuScene(MenuScene&&) = delete;
		MenuScene& operator=(MenuScene&&) = delete;
		~MenuScene() = default;
	private:
		SelectionMenuComponent* m_pSelectionMenuComponent{};
	};
}