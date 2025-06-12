#pragma once
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <optional>
#include "Singleton.h"
#include "GameObject.h"
#include "Scene.h"

namespace dae
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		// Adds a scene by pointer
		void AddScene(std::unique_ptr<Scene> scene);

		// Removes a scene
		void RemoveScene(const std::string& name);

		// Sets the scene to a singular scene
		void SetScene(const std::string& name);

		Scene* GetActiveScene() const;

		void FixedUpdate();
		void Update(float deltaTime);
		void Render();
	private:
		std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;

		// There is no reason to run more than a single scene at a time
		Scene* m_activeScene{};

		std::optional<std::string> m_nextScene;
	};
}
