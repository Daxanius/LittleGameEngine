#pragma once
#include <string>
#include <vector>

#include "GameObject.h"
#include "BaseComponent.h"

namespace dae {
	class ThrashTheCacheComponent : public BaseComponent {
	public:
		struct Transform {
			float matrix[16] = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1 };
		};

		class GameObject3D {
		public:
			Transform transform;
			int ID;
		};

		ThrashTheCacheComponent(GameObject& pOwner, int samples = 1, int dataSize = 100000000);

		void FixedUpdate() override {};
		void Update(float) override {};
		void Render() override;
		void PostUpdate() override {};
	private:
		void GenerateUsingIntegers();
		void GenerateUsingObjects();

		std::vector<float> m_iterations{};
		std::vector<float> m_timingData{};

		int m_samples;
		int m_dataSize;

		float m_maxTimeTaken{};

		bool m_hasGeneratedData{};
	};
}

