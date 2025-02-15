#pragma once
#include "GameObject.h"
#include "Texture2D.h"
#include "Component.h"
#include "TransformComponent.h"

namespace dae {
	class TextureComponent final : public Component {
	public:
		TextureComponent(const std::string& filename);

		void Ready(GameObject* obj) override;
		void Render() const override;
	private:
		std::shared_ptr<Texture2D> m_Texture;

		TransformComponent* m_Transform{ nullptr };
	};
}
