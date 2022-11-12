#include "game.h"

json OpenInitFile() {
    std::string path = "resources/config.json";
    json data;
    try {
        std::ifstream f(path);
        data = json::parse(f);
    }
    catch (...) {
        Logger::error("Config", __func__, "Error when parsing " + path + ". Aborting.");
        exit(2);
    }
    return data;
}

void GameLoop() {
    json data = OpenInitFile();
    Config::InitConf(data);
    Game game(data);
    game.MainLoop();
}



Game::Game(json json)
    : window("Pokemon"), input()
{
    srand((unsigned int)time(NULL));
    input.InitKeys(json["keys"]);
    std::shared_ptr<SceneSplashScreen> splashScreen = std::make_shared<SceneSplashScreen>(workingDir, sceneStateMachine, window, textureAllocator);
    std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>(workingDir, textureAllocator, window, input);

    unsigned int splashScreenID = sceneStateMachine.Add(splashScreen);
    unsigned int gameSceneID = sceneStateMachine.Add(gameScene);
    splashScreen->SetSwitchToScene(gameSceneID);
    sceneStateMachine.SwitchTo(gameSceneID);
    deltaTime = clock.restart().asSeconds();
}

void Game::MainLoop() {
    while (IsRunning())
    {
        CaptureInput();
        Update();
        LateUpdate();
        Draw();
        CalculateDeltaTime();
    }
}
