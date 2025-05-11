#pragma once

namespace dae {
	class CoilyComponent;

	class AbstractCoilyState {
	public:
		virtual void OnEnter() = 0;

		virtual void Update(float deltaTime) = 0;

		virtual void OnExit() = 0;

		CoilyComponent* GetCoilyComponent() const;
	protected:
		AbstractCoilyState(CoilyComponent* pCoilyComponent);

	private:
		CoilyComponent* m_pCoilyComponent;
	};
}
