#pragma once
#include "GameObject.h"
#include "Texture2D.h"
#include "Component.h"
#include "TransformComponent.h"

namespace dae {
	class TextureComponent final : public Component {
	public:
		TextureComponent(GameObject& pOwner, const std::string& filename);

		void FixedUpdate() override {};
		void Update(float) override {};
		void Render() const override;
		void PostUpdate() override;
	private:
		std::shared_ptr<Texture2D> m_pTexture;

		TransformComponent* m_pTransformComponent{ nullptr };
	};
}
