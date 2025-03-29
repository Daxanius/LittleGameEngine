#pragma once
#include "GameObject.h"
#include "Texture2D.h"
#include "BaseComponent.h"

namespace dae {
	class TextureComponent final : public BaseComponent {
	public:
		TextureComponent(GameObject& pOwner, const std::string& filename);

		void FixedUpdate() override {};
		void Update(float) override {};
		void Render() override;
		void PostUpdate() override {};
	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}
