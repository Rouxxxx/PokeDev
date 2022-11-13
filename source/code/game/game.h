#pragma once
#include "../windowManager/window.h"
#include "../utils/workingDirectory.h"
#include "../windowManager/input.h"
#include "../scene/sceneStateMachine.h"
#include "../scene/sceneSplashScreen/sceneSplashScreen.h"
#include "../scene/sceneGame/sceneGame.h"
#include "../Logger/logger.h"
#include "config/config.h"

void GameLoop();

class Game
{
public:
    Game(json);
    void MainLoop();
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
    SoundFactory soundFactory;
};