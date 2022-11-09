#include "sceneSplashScreen.h"

SceneSplashScreen::SceneSplashScreen(WorkingDirectory& workingDir, SceneStateMachine& sceneStateMachine, Window& window, ResourceAllocator<sf::Texture>& textureAllocator)
	: sceneStateMachine(sceneStateMachine), workingDir(workingDir), window(window), switchToState(0), currentSeconds(0.f), showForSeconds(3.f), textureAllocator(textureAllocator)
{}


void SceneSplashScreen::OnCreate()
{
	int textureID = textureAllocator.add(workingDir.Get() + "image0.png");

	if (textureID <= 0)
		return;

	std::shared_ptr<sf::Texture> texture = textureAllocator.get(textureID);
	splashSprite.setTexture(*texture);
	sf::FloatRect spriteSize = splashSprite.getLocalBounds();
	splashSprite.setOrigin(spriteSize.width * 0.5f, spriteSize.height * 0.5f);
	splashSprite.setScale(0.5f, 0.5f);
	sf::Vector2f windowCentre = window.GetCentre();
	splashSprite.setPosition(windowCentre.x, windowCentre.y);
}

void SceneSplashScreen::OnActivate()
{
	// Resets the currentSeconds count whenever the scene is activated.
	currentSeconds = 0.f;
}
void SceneSplashScreen::OnDestroy() { }

void SceneSplashScreen::SetSwitchToScene(unsigned int id) {
	switchToState = id;
}
void SceneSplashScreen::Update(float deltaTime)
{
	currentSeconds += deltaTime;
	if (currentSeconds >= showForSeconds)
		sceneStateMachine.SwitchTo(switchToState);
}
void SceneSplashScreen::Draw(Window& window)
{
	window.Draw(splashSprite);
}
