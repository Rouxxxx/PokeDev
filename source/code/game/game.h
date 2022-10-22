#pragma once
#include "../windowManager/window.h"
#include "../utils/workingDirectory.h"
#include "../windowManager/input.h"
#include "../scene/sceneStateMachine.h"
#include "../scene/managedScenes/sceneSplashScreen.h"
#include "../scene/managedScenes/sceneGame.h"

class Game
{
public:
    Game();
    void ProcessInput();
    void Update();
    void LateUpdate();
    void Draw();
    void CalculateDeltaTime();
    bool IsRunning() const;
    void CaptureInput();

private:
    Window window;
    WorkingDirectory workingDir;

    sf::Texture ethanTexture;
    sf::Sprite ethanSprite;

    sf::Clock clock;
    float deltaTime;

    Input input;
    SceneStateMachine sceneStateMachine;

    ResourceAllocator<sf::Texture> textureAllocator;
};