#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include <string>
#include <memory>

namespace dae {
	class Font;
	class Texture2D;

	// A more complex version of the text component with newline support
	class ParagraphComponent final : public BaseComponent {
	public:
		ParagraphComponent(GameObject& pOwner, const std::string& text, std::shared_ptr<Font> font, float lineSpacing = 5.f);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override;

		void SetText(const std::string& text);

		ParagraphComponent(const ParagraphComponent&) = delete;
		ParagraphComponent& operator=(const ParagraphComponent&) = delete;
		ParagraphComponent(ParagraphComponent&&) = delete;
		ParagraphComponent& operator=(ParagraphComponent&&) = delete;
		~ParagraphComponent() = default;
	private:
		bool m_needsUpdate;
		std::string m_Text;
		float m_lineSpacing;

		std::shared_ptr<Font> m_pFont;
		std::vector<std::shared_ptr<Texture2D>> m_lineTextures;
	};
}

