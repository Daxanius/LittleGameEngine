#include "ThrashTheCacheComponent.h"

#include <imgui.h>
#include <imgui_plot.h>
#include <chrono>

dae::ThrashTheCacheComponent::ThrashTheCacheComponent(GameObject& pOwner, int samples, int dataSize) : BaseComponent(pOwner), m_samples(samples), m_dataSize(dataSize) {

}

void dae::ThrashTheCacheComponent::Render() {
	// ImGui::SetNextWindowSizeConstraints(ImVec2(200, 100), ImVec2(FLT_MAX, FLT_MAX));
	ImGui::Begin("Thrash The Cache", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Generate Data Using Integers")) {
		GenerateUsingIntegers();
	};

	if (ImGui::Button("Generate Data Using Objects")) {
		GenerateUsingObjects();
	};

	if (m_hasGeneratedData) {
		ImGui::PlotConfig conf;
		conf.values.xs = m_iterations.data();
		conf.values.ys = m_timingData.data();
		conf.values.count = static_cast<int>(m_iterations.size());
		conf.scale.min = 0;
		conf.scale.max = m_maxTimeTaken;
		conf.tooltip.show = true;
		conf.tooltip.format = "Sep Size: %.2f, Time in Seconds: %.2f";
		conf.frame_size = ImVec2(300, 140);
		conf.line_thickness = 2.f;
		ImGui::Plot("plot1", conf);
	}

	ImGui::End();
}

void dae::ThrashTheCacheComponent::GenerateUsingIntegers() {
	std::vector<int> values{ std::vector<int>(m_dataSize, 2) };
	m_maxTimeTaken = 0.f;
	m_iterations.clear();
	m_timingData.clear();

	for (size_t stepSize = 1; stepSize <= 1024; stepSize *= 2) {
		double totalTime = 0.0;

		for (int run = 0; run < m_samples; ++run) {
			auto start = std::chrono::high_resolution_clock::now();

			for (size_t valueIndex{}; valueIndex < values.size(); valueIndex += stepSize) {
				values[valueIndex] *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> duration = end - start;
			totalTime += duration.count();
		}

		double averageTime{ totalTime / m_samples };
		m_timingData.push_back(static_cast<float>(averageTime));
		m_iterations.push_back(static_cast<float>(stepSize));
		m_maxTimeTaken = std::max(m_maxTimeTaken, static_cast<float>(averageTime));
	}

	values.clear();
	m_hasGeneratedData = true;
}

void dae::ThrashTheCacheComponent::GenerateUsingObjects() {
	auto values{ std::vector<dae::ThrashTheCacheComponent::GameObject3D>(m_dataSize, dae::ThrashTheCacheComponent::GameObject3D{}) };
	m_maxTimeTaken = 0.f;
	m_iterations.clear();
	m_timingData.clear();

	for (size_t stepSize = 1; stepSize <= 1024; stepSize *= 2) {
		double totalTime = 0.0;

		for (int run = 0; run < m_samples; ++run) {
			auto start = std::chrono::high_resolution_clock::now();

			for (size_t valueIndex{}; valueIndex < values.size(); valueIndex += stepSize) {
				values[valueIndex].ID += 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> duration = end - start;
			totalTime += duration.count();
		}

		double averageTime{ totalTime / m_samples };
		m_timingData.push_back(static_cast<float>(averageTime));
		m_iterations.push_back(static_cast<float>(stepSize));
		m_maxTimeTaken = std::max(m_maxTimeTaken, static_cast<float>(averageTime));
	}

	values.clear();
	m_hasGeneratedData = true;
}
