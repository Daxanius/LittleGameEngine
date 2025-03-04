#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "Scene.h"
#include "FpsComponent.h"
#include "RotatorComponent.h"
#include "ThrashTheCacheComponent.h"

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// Create the background object
	auto backgroundObject{ std::make_shared<dae::GameObject>() };
	backgroundObject->AddComponent<dae::TextureComponent>("background.tga");
	scene.Add(backgroundObject);

	// Create the logo object
	auto logoObject{ std::make_shared<dae::GameObject>(std::move(dae::Transform(216.f, 180.f))) };
	logoObject->AddComponent<dae::TextureComponent>("logo.tga");
	scene.Add(logoObject);

	// Create the title object
	auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };

	auto titleObject{ std::make_shared<dae::GameObject>(std::move(dae::Transform(80.f, 20.f))) };
	titleObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	scene.Add(titleObject);

	// Create the FPS object
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	auto fpsObject{ std::make_shared<dae::GameObject>() };
	fpsObject->AddComponent<dae::TextComponent>("FPS", font);
	fpsObject->AddComponent<dae::FpsComponent>();
	scene.Add(fpsObject);

	// Create orbiting objects
	auto orbitOrigin{ std::make_shared<dae::GameObject>(std::move(dae::Transform(200.f, 200.f))) };
	scene.Add(orbitOrigin);

	auto orbitObject{ std::make_shared<dae::GameObject>() };
	orbitObject->AddComponent<dae::TextureComponent>("qbert_char.png");
	orbitObject->AddComponent<dae::RotatorComponent>(5.f, 50.f);
	scene.Add(orbitObject);

	orbitObject->SetParent(orbitOrigin.get(), false);

	// Child of orbit object
	auto childOrbitObject{ std::make_shared<dae::GameObject>() };
	childOrbitObject->AddComponent<dae::TextureComponent>("qbert_char.png");
	childOrbitObject->AddComponent<dae::RotatorComponent>(10.f, 20.f);
	scene.Add(childOrbitObject);

	childOrbitObject->SetParent(orbitObject.get(), false);

	auto thrashTheCacheObject{ std::make_shared<dae::GameObject>() };
	thrashTheCacheObject->AddComponent<dae::ttc::ThrashTheCacheComponent>();
	scene.Add(thrashTheCacheObject);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}