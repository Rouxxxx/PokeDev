#include "sceneGame.h"

void SceneGame::InitMap(std::string path) {

	std::string funcName = __func__;
	std::ifstream f(path);
	json data = json::parse(f);

	auto& meta = data["map"]["meta"];
	auto& players = data["map"]["players"];

	std::string tilemap = meta["tilemap"];
	std::string type = meta["type"];

	sf::Vector2i mapOffset(16, 0);
	std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse(workingDir.Get() + tilemap, mapOffset, &collider);
	objects.Add(levelTiles);

	auto pos = path.find_last_of("/");
	Logger::info(className, __func__, "Map successfully created   (" + path.substr(pos + 1, path.size()) + ")");

	InitPNJs(players);
};