#pragma once
#include "GameObject.h"
#include "Texture2D.h"
#include "BaseComponent.h"

namespace dae {
	class TextureComponent final : public BaseComponent {
	public:
		TextureComponent(GameObject& pOwner, const std::string& filename, float scale = 1.f);

		void FixedUpdate() override {};
		void Update(float) override {};
		void Render() override;
		void PostUpdate() override {};

		TextureComponent(const TextureComponent&) = delete;
		TextureComponent& operator=(const TextureComponent&) = delete;
		TextureComponent(TextureComponent&&) = delete;
		TextureComponent& operator=(TextureComponent&&) = delete;
		~TextureComponent() = default;
	private:
		std::shared_ptr<Texture2D> m_pTexture;

		float m_scale;
	};
}
