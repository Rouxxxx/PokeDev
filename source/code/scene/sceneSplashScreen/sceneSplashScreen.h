#pragma once

#include <SFML/Graphics.hpp>
#include "../sceneStateMachine.h"
#include "../../utils/workingDirectory.h"
#include "../../resource/resourceAllocator.h"


class SceneSplashScreen : public Scene
{
public:
	SceneSplashScreen(WorkingDirectory& workingDir, SceneStateMachine& sceneStateMachine, Window& window, ResourceAllocator<sf::Texture>& textureAllocator);

	void OnCreate() override;
	void OnDestroy() override;
	void OnActivate() override;
	void SetSwitchToScene(unsigned int id);
	void Update(float deltaTime) override;
	void Draw(Window& window) override;
private:
	ResourceAllocator<sf::Texture>& textureAllocator;

	sf::Texture splashTexture;
	sf::Sprite splashSprite;
	WorkingDirectory& workingDir;
	SceneStateMachine& sceneStateMachine;
	Window& window;
	// We want to show this scene for a set amount of time
	float showForSeconds;
	// How long the scene has currently been visible.
	float currentSeconds;
	// The state we want to transition to when this scenes time expires.
	unsigned int switchToState;
};
