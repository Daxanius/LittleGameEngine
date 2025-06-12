#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <string>
#include <vector>
#include <memory>

namespace dae {
	struct Tile {
		int state = 0;
	};

	class RhombilleGridComponent : public BaseComponent {
	public:
		RhombilleGridComponent(GameObject& pOwner, const std::string& texturePath, int tileWidth, int tileHeight, int rows, float scale = 1.f);

		void FixedUpdate() override {}
		void Update(float) override {}
		void PostUpdate() override {};
		void Render() override;

		void SetVariant(int variant);
		int GetVariant() const;

		glm::vec2 ToWorldPosition(int row, int col);
		std::pair<int, int> ToGridCoords(const glm::vec2& worldPos) const;

		bool AreAllTilesState(int state) const;

		void SetAllStates(int state);

		// Grid access
		Tile* GetTile(int row, int col);

		void GetRandomTile(int& row, int& col) const;
		int GetRandomCol(int row) const;

		int GetRows() const;

		int GetTileWidth() const;
		int GetTileHeight() const;
		float GetScale() const;
	private:
		int m_rows;
		int m_tileWidth;
		int m_tileHeight;

		float m_scale;

		int m_variant;

		std::vector<std::vector<Tile>> m_tiles;
		std::shared_ptr<Texture2D> m_pTexture;
	};
}
