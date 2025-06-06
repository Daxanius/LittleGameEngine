#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
	public:
		explicit Scene(const std::string& name);

		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

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
		void RemoveDestroyedObjects();

		std::string m_name;
		std::vector <std::shared_ptr<GameObject>> m_objects{};

		std::vector<std::shared_ptr<GameObject>> m_objectsToAdd{};
		std::vector<std::shared_ptr<GameObject>> m_objectsToRemove{};

		static unsigned int m_idCounter; 
	};
}
