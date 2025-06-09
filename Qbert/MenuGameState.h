#pragma once
#include "AbstractGameState.h"
#include "SelectionMenuComponent.h"
#include "Scene.h"
#include <memory>

namespace dae {
	class MenuGameState final : public AbstractGameState {
	public:
		MenuGameState();

		void OnEnter() override;


		MenuGameState(const MenuGameState&) = delete;
		MenuGameState& operator=(const MenuGameState&) = delete;
		MenuGameState(MenuGameState&&) = delete;
		MenuGameState& operator=(MenuGameState&&) = delete;
		~MenuGameState() = default;
	private:
		std::shared_ptr<Scene> m_pScene;

		std::shared_ptr<AbstractGameState> m_pSinglePlayerState;

		SelectionMenuComponent* m_pSelectionMenuComponent{};
	};
}