#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		// Adds a scene by pointer
		void AddScene(std::shared_ptr<Scene> scene);

		// Removes a scene by pointer
		void RemoveScene(std::shared_ptr<Scene> scene);

		// Sets the scene to a singular scene
		void SetScene(std::shared_ptr<Scene> scene);

		void FixedUpdate();
		void Update(float deltaTime);
		void Render();
	private:
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
