#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(GameObject& pOwner, const std::string& text, std::shared_ptr<Font> font);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void Render() override;
		void PostUpdate() override {};

		void SetText(const std::string& text);

		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_needsUpdate;
		std::string m_Text;

		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
