#pragma once
#include <string>
#include <functional>

namespace dae
{
	class Minigin final
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		constexpr static float FIXED_UPDATE_INTERVAL{ .02f };
		constexpr static float TARGET_FPS{ 60.0f };
		constexpr static float FRAME_TIME{ 1.0f / TARGET_FPS };
	};
}