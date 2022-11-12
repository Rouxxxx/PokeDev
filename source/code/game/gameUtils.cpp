#include "game.h"

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
