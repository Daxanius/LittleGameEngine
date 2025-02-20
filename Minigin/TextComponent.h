#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(GameObject& pOwner, const std::string& text, std::shared_ptr<Font> font);

		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void Render() const override;
		void PostUpdate() override;

		void SetText(const std::string& text);
	private:
		bool m_NeedsUpdate;
		std::string m_Text;

		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;

		TransformComponent* m_pTransformComponent{ nullptr };
	};
}
