#include "ThrashTheCacheComponent.h"

#include <imgui.h>
#include <imgui_plot.h>
#include <chrono>

dae::ttc::ThrashTheCacheComponent::ThrashTheCacheComponent(GameObject& pOwner, int samples, int dataSize) : BaseComponent(pOwner), m_samples(samples), m_dataSize(dataSize) {

}

void dae::ttc::ThrashTheCacheComponent::Render() {
	// ImGui::SetNextWindowSizeConstraints(ImVec2(200, 100), ImVec2(FLT_MAX, FLT_MAX));
	ImGui::Begin("Thrash The Cache", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Generate Data Using Integers")) {
		GenerateUsingIntegers();
	};

	if (ImGui::Button("Generate Data Using Objects")) {
		GenerateUsingObjects();
	};

	if (ImGui::Button("Generate Data Using Alt Objects")) {
		GenerateUsingAltObjects();
	};

	// Alt game objects graph
	if (m_intGraph.hasGeneratedData) {
		ImGui::LabelText("", "Integer Graph:");

		ImGui::PlotConfig conf;
		conf.values.xs = m_intGraph.iterations.data();
		conf.values.ys = m_intGraph.timingData.data();
		conf.values.count = static_cast<int>(m_intGraph.iterations.size());
		conf.scale.min = 0;
		conf.scale.max = m_intGraph.maxTimeTaken;
		conf.tooltip.show = true;
		conf.tooltip.format = "Sep Size: %.2f, Time in Seconds: %.2f";
		conf.frame_size = ImVec2(300, 140);
		conf.line_thickness = 2.f;
		ImGui::Plot("Integers", conf);
	}

	// Colors for object graphs
	const ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0) };

	// Game Objects graph
	if (m_gameObjectGraph.hasGeneratedData) {
		ImGui::LabelText("", "Game Object Graph:");

		ImGui::PlotConfig conf;
		conf.values.xs = m_gameObjectGraph.iterations.data();
		conf.values.ys = m_gameObjectGraph.timingData.data();
		conf.values.count = static_cast<int>(m_gameObjectGraph.iterations.size());
		conf.values.color = colors[1];
		conf.scale.min = 0;
		conf.scale.max = m_gameObjectGraph.maxTimeTaken;
		conf.tooltip.show = true;
		conf.tooltip.format = "Sep Size: %.2f, Time: %.2f";
		conf.frame_size = ImVec2(300, 140);
		conf.line_thickness = 2.f;
		ImGui::Plot("Game Objects", conf);
	}


	// Alt game objects graph
	if (m_altGameObjectGraph.hasGeneratedData) {
		ImGui::LabelText("", "Alt Game Object Graph:");

		ImGui::PlotConfig conf;
		conf.values.xs = m_altGameObjectGraph.iterations.data();
		conf.values.ys = m_altGameObjectGraph.timingData.data();
		conf.values.count = static_cast<int>(m_altGameObjectGraph.iterations.size());
		conf.values.color = colors[0];
		conf.scale.min = 0;
		conf.scale.max = m_altGameObjectGraph.maxTimeTaken;
		conf.tooltip.show = true;
		conf.tooltip.format = "Sep Size: %.2f, Time: %.2f";
		conf.frame_size = ImVec2(300, 140);
		conf.line_thickness = 2.f;
		ImGui::Plot("Alt Game Objects", conf);
	}

	if (m_altGameObjectGraph.hasGeneratedData && m_gameObjectGraph.hasGeneratedData) {
		ImGui::LabelText("", "Combined Object Graph:");

		// Create an array of pointers for timing data
		const float* ys_data[] = {
				m_altGameObjectGraph.timingData.data(),
				m_gameObjectGraph.timingData.data()
		};

		ImGui::PlotConfig conf;
		conf.values.xs = m_altGameObjectGraph.iterations.data();
		conf.values.ys_list = ys_data;
		conf.values.ys_count = 2;
		conf.values.colors = colors;
		conf.values.count = static_cast<int>(m_altGameObjectGraph.iterations.size());
		conf.scale.min = 0;
		conf.scale.max = std::max<float>(m_gameObjectGraph.maxTimeTaken, m_altGameObjectGraph.maxTimeTaken);
		conf.tooltip.show = true;
		conf.tooltip.format = "Sep Size: %.2f, Time: %.2f";
		conf.frame_size = ImVec2(300, 140);
		conf.line_thickness = 2.f;
		ImGui::Plot("Alt Game Objects & Normal Game Objects", conf);
	}

	ImGui::End();
}

void dae::ttc::ThrashTheCacheComponent::GenerateUsingIntegers() {
	std::vector<int> values{ std::vector<int>(m_dataSize, 2) };
	m_intGraph.maxTimeTaken = 0.f;
	m_intGraph.iterations.clear();
	m_intGraph.timingData.clear();

	for (size_t stepSize = 1; stepSize <= 1024; stepSize *= 2) {
		long long totalTime{};

		for (int run = 0; run < m_samples; ++run) {
			auto start = std::chrono::high_resolution_clock::now();

			for (size_t valueIndex{}; valueIndex < values.size(); valueIndex += stepSize) {
				values[valueIndex] *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			totalTime += total;
		}

		long long averageTime{ totalTime / m_samples };
		m_intGraph.timingData.push_back(static_cast<float>(averageTime));
		m_intGraph.iterations.push_back(static_cast<float>(stepSize));
		m_intGraph.maxTimeTaken = std::max(m_intGraph.maxTimeTaken, static_cast<float>(averageTime));
	}

	values.clear();
	m_intGraph.hasGeneratedData = true;
}

void dae::ttc::ThrashTheCacheComponent::GenerateUsingObjects() {
	auto values{ std::vector<dae::ttc::GameObject3D>(m_dataSize, dae::ttc::GameObject3D{}) };
	m_gameObjectGraph.maxTimeTaken = 0.f;
	m_gameObjectGraph.iterations.clear();
	m_gameObjectGraph.timingData.clear();

	for (size_t stepSize = 1; stepSize <= 1024; stepSize *= 2) {
		long long totalTime{};

		for (int run = 0; run < m_samples; ++run) {
			auto start = std::chrono::high_resolution_clock::now();

			for (size_t valueIndex{}; valueIndex < values.size(); valueIndex += stepSize) {
				values[valueIndex].ID += 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			totalTime += total;
		}

		long long averageTime{ totalTime / m_samples };
		m_gameObjectGraph.timingData.push_back(static_cast<float>(averageTime));
		m_gameObjectGraph.iterations.push_back(static_cast<float>(stepSize));
		m_gameObjectGraph.maxTimeTaken = std::max(m_gameObjectGraph.maxTimeTaken, static_cast<float>(averageTime));
	}

	values.clear();
	m_gameObjectGraph.hasGeneratedData = true;
}

void dae::ttc::ThrashTheCacheComponent::GenerateUsingAltObjects() {
	auto values{ std::vector<dae::ttc::GameObject3DAlt>(m_dataSize, dae::ttc::GameObject3DAlt{}) };
	m_altGameObjectGraph.maxTimeTaken = 0.f;
	m_altGameObjectGraph.iterations.clear();
	m_altGameObjectGraph.timingData.clear();

	for (size_t stepSize = 1; stepSize <= 1024; stepSize *= 2) {
		long long totalTime{};

		for (int run = 0; run < m_samples; ++run) {
			auto start = std::chrono::high_resolution_clock::now();

			for (size_t valueIndex{}; valueIndex < values.size(); valueIndex += stepSize) {
				values[valueIndex].ID += 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			totalTime += total;
		}

		long long averageTime{ totalTime / m_samples };
		m_altGameObjectGraph.timingData.push_back(static_cast<float>(averageTime));
		m_altGameObjectGraph.iterations.push_back(static_cast<float>(stepSize));
		m_altGameObjectGraph.maxTimeTaken = std::max(m_altGameObjectGraph.maxTimeTaken, static_cast<float>(averageTime));
	}

	values.clear();
	m_altGameObjectGraph.hasGeneratedData = true;
}
