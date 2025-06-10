#pragma once
#include <BaseComponent.h>
#include <string>
#include <vector>
#include "Font.h"
#include "Texture2D.h"

namespace dae {
	// A component that takes text input and displays it using a text component
	class TextInputComponent final : public BaseComponent {
	public:
		TextInputComponent(GameObject& pOwner, int stringSize, std::shared_ptr<Font> font, int characterSpacing = 10);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override;

		void Left();
		void Right();
		void Up();
		void Down();

		const std::string& GetValue();

		TextInputComponent(const TextInputComponent&) = delete;
		TextInputComponent& operator=(const TextInputComponent&) = delete;
		TextInputComponent(TextInputComponent&&) = delete;
		TextInputComponent& operator=(TextInputComponent&&) = delete;
		~TextInputComponent() = default;
	private:
		static constexpr std::string_view AVAILABLE_CHARACTERS = "_ABCDEFHHIJKLMNOPQRSTUVWXYZ";

		std::shared_ptr<Font> m_font;

		int m_stringSize;
		int m_characterSpacing;

		std::string m_textValue;
		std::vector<int> m_values;

		int m_characterIndex{};
		bool m_needsUpdate{ true };

		std::vector<std::shared_ptr<Texture2D>> m_characterTextures;
		std::shared_ptr<Texture2D> m_caretTexture;
	};
}

