#pragma once
#include <BaseComponent.h>
#include "Texture2D.h"
#include <string>

namespace dae{
	class RepeatingTextureComponent : public BaseComponent {
	public:
		RepeatingTextureComponent(GameObject& pOwner, const std::string& texturePath, int textureWidth, int textureHeight, int textureOffsetX, int textureOffsetY, float padding, float scale = 1.f);
	
		void SetRows(int rows);
		void SetCols(int cols);

		void FixedUpdate() override {};
		void Update(float) override {};
		void PostUpdate() override {};
		void Render() override;
	private:
		int m_textureWidth;
		int m_textureHeight;
		int m_textureOffsetX;
		int m_textureOffsetY;

		float m_padding;
		float m_scale;

		int m_rows{};
		int m_cols{};

		std::shared_ptr<Texture2D> m_pTexture;
	};
}

