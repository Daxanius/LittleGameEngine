#pragma once
#include "SceneManager.h"
#include <memory>

namespace dae
{
	class GameObject;
	class Scene final
	{
	public:
		explicit Scene(const std::string& name);

		void Add(std::unique_ptr<GameObject>&& object);
		void RemoveAll();

		void OnEnter();

		void FixedUpdate();
		void Update(float deltaTime);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		void ProcessPendingChanges();

		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_objects{};
		std::vector<std::unique_ptr<GameObject>> m_objectsToAdd{};

		static unsigned int m_idCounter; 
	};
}
