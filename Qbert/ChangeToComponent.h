#pragma once
#include <BaseComponent.h>
#include "LevelComponent.h"
#include "Texture2D.h"
#include <memory>

namespace dae {
	class ChangeToComponent final : public BaseComponent {
	public:
		ChangeToComponent(GameObject& pOwner, LevelComponent* pLevelComponent, const std::string& texturePath, int tileWidth, int tileHeight, float scale = 1.f);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override;

	private:
		LevelComponent* m_pLevelComponent;

		std::shared_ptr<Texture2D> m_pTexture;

		int m_tileWidth;
		int m_tileHeight;

		float m_scale;
	};
}
