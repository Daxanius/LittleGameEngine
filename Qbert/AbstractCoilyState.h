#pragma once

namespace dae {
	class CoilyComponent;

	class AbstractCoilyState {
	public:
		virtual ~AbstractCoilyState() = default;

		virtual void OnEnter() = 0;

		virtual void Update(float deltaTime) = 0;

		virtual void OnExit() = 0;

		CoilyComponent* GetCoilyComponent() const;


		AbstractCoilyState(const AbstractCoilyState&) = delete;
		AbstractCoilyState& operator=(const AbstractCoilyState&) = delete;
		AbstractCoilyState(AbstractCoilyState&&) = delete;
		AbstractCoilyState& operator=(AbstractCoilyState&&) = delete;
	protected:
		AbstractCoilyState(CoilyComponent* pCoilyComponent);

	private:
		CoilyComponent* m_pCoilyComponent;
	};
}
