#pragma once
#include "SelectionMenuComponent.h"
#include <Command.h>


namespace dae {
	class MenuCommand : public Command {
	public:
		enum Action {
			Previous,
			Next,
			Confirm
		};

		MenuCommand(SelectionMenuComponent* pSelectionMenuComponent, Action action);

		void Execute() override;
	private:
		SelectionMenuComponent* m_pSelectionMenuComponent;
		Action m_action;
	};
}
