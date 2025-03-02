#pragma once
#include <string>
#include <vector>

#include "GameObject.h"
#include "BaseComponent.h"

namespace dae {
	namespace ttc {
		struct Transform {
			float matrix[16] = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1 };
		};

		class GameObject3D final {
		public:
			Transform transform;
			int ID;
		};

		class GameObject3DAlt final {
		public:
			Transform* transform;
			int ID;
		};

		struct GraphData {
			std::vector<float> iterations{};
			std::vector<float> timingData{};
			float maxTimeTaken{};
			bool hasGeneratedData;
		};

		class ThrashTheCacheComponent final : public BaseComponent {
		public:
			ThrashTheCacheComponent(GameObject& pOwner, int samples = 1, int dataSize = 100000000);

			void FixedUpdate() override {};
			void Update(float) override {};
			void Render() override;
			void PostUpdate() override {};
		private:
			void GenerateUsingIntegers();
			void GenerateUsingObjects();
			void GenerateUsingAltObjects();

			int m_samples;
			int m_dataSize;

			GraphData m_gameObjectGraph{};
			GraphData m_altGameObjectGraph{};
			GraphData m_intGraph{};
		};
	}
}

