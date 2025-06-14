#pragma once
#include "BaseComponent.h"
#include "Command.h"
#include "Font.h"
#include "Texture2D.h"
#include "Color.h"
#include "Subject.h"
#include <string>

namespace dae {
	class SelectionMenuComponent : public BaseComponent {
	public:
		struct Option {
			std::string text;
			std::unique_ptr<Command> command;
		};

		SelectionMenuComponent(GameObject& pOwner, std::shared_ptr<Font> font, const Color& color, int padding, std::shared_ptr<Texture2D> pSelectionArrowTexture);

		void AddOption(Option&& option);

		void NextOption();
		void PreviousOption();
		void ConfirmOption();

		void FixedUpdate() override {};
		void Update(float) override {};
		void PostUpdate() override {};
		void Render() override;

		Subject& GetSubject();


		SelectionMenuComponent(const SelectionMenuComponent&) = delete;
		SelectionMenuComponent& operator=(const SelectionMenuComponent&) = delete;
		SelectionMenuComponent(SelectionMenuComponent&&) = delete;
		SelectionMenuComponent& operator=(SelectionMenuComponent&&) = delete;
		~SelectionMenuComponent() = default;

	private:
		std::shared_ptr<Texture2D> CreateTextureFromText(const std::string& text);

		Color m_Color;
		int m_padding;
		std::shared_ptr<Font> m_pFont;

		std::vector<std::shared_ptr<Texture2D>> m_optionTextures;
		std::vector<std::unique_ptr<Command>> m_optionCommands;
		std::shared_ptr<Texture2D> m_pSelectionArrowTexture;

		int m_currentOption{};
		int m_widestWidth{};

		Subject m_subject;
	};
}