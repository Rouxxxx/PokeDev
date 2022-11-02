#include "game.h"

Game::Game()
    : window("Pokemon")
{
    srand(time(NULL));
    std::shared_ptr<SceneSplashScreen> splashScreen = std::make_shared<SceneSplashScreen>(workingDir, sceneStateMachine, window, textureAllocator);
    std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>(workingDir, textureAllocator, window);

    unsigned int splashScreenID = sceneStateMachine.Add(splashScreen);
    unsigned int gameSceneID = sceneStateMachine.Add(gameScene);
    splashScreen->SetSwitchToScene(gameSceneID);
    sceneStateMachine.SwitchTo(gameSceneID);
    deltaTime = clock.restart().asSeconds();
}

void Game::ProcessInput()
{
    sceneStateMachine.ProcessInput();
}
void Game::Update()
{
    window.Update();
    sceneStateMachine.Update(deltaTime);
}
void Game::LateUpdate()
{
    sceneStateMachine.LateUpdate(deltaTime);
}
void Game::Draw()
{
    window.BeginDraw();
    sceneStateMachine.Draw(window);
    window.EndDraw();
}

bool Game::IsRunning() const
{
    return window.IsOpen();
}

void Game::CalculateDeltaTime()
{
    deltaTime = clock.restart().asSeconds();
}


void Game::CaptureInput()
{
    sceneStateMachine.ProcessInput();
}

