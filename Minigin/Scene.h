#pragma once
#include <memory>
#include <string>
#include <vector>

namespace dae
{
	class GameObject;

	// I made scene abstract because I personally prefer this structure
	// and it allows me to run custom logic for every scene when a scene changes
	// (like recreating objects etc). Not only that, but it also allows
	// me to avoid global state by having custom scene constructors
	// that can take in some settings and construct the scene based on those
	// This system is waaay more powerful IMO, though perhaps I am not seeing something
	// that experienced game devs do see. This system is way more flexible / powerful
	// and doesn't require me juggling around values in awkward ways anymore
	// This is also a case of inherit to be re-used :)
	class Scene {
	public:
		explicit Scene(const std::string& name);

		void Add(std::unique_ptr<GameObject>&& object);
		void RemoveAll();

		// Resets the scene and sets it up again (or initially sets it up)
		void Setup();

		// Called when the scene becomes active
		void Enter();

		void FixedUpdate();
		void Update(float deltaTime);
		void Render() const;

		const std::string& GetName() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		virtual void OnSetup() {};
		virtual void OnEnter() {};

		void SetName(const std::string& name);
	private: 
		void ProcessPendingChanges();

		static unsigned int m_idCounter; 

		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_objects{};
		std::vector<std::unique_ptr<GameObject>> m_objectsToAdd{};

		mutable std::vector<const GameObject*> m_sortedRenderables{};
		mutable bool m_sortDirty{ true };
	};
}
