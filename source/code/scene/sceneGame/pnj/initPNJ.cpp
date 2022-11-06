#include "../sceneGame.h"
#include "c_pnj.h"

void SceneGame::InitPNJs(reference players) {
	std::ifstream f2("resources/sprites/trainers/trainers.json");
	json data2 = json::parse(f2);
	auto& meta2 = data2["trainers"]["meta"];
	auto moves = data2["trainers"]["moves"];

	int width = meta2["width"];
	int height = meta2["height"];
	int sortOrder = meta2["sortOrder"];
	float scale = meta2["scale"];
	std::string image = meta2["image"];
	int TextureID = textureAllocator.add(workingDir.Get() + image);

	pnjWidth = meta2["pnjWidth"];
	pnjHeight = meta2["pnjHeight"];

	int offsetWidth = meta2["offsetWidth"];
	int offsetHeight = meta2["offsetHeight"];


	for (auto it = players.begin(); it != players.end(); it++) {
		auto currentPlayerIt = *it;
		int idPNJ = currentPlayerIt["id"];

		int currentWidth = idPNJ % width;
		int currentHeight = idPNJ / width;

		sf::Vector2i offset = sf::Vector2i(currentWidth * offsetWidth, currentHeight * offsetHeight);

		std::string style = currentPlayerIt["style"];

		bool isTrainer = currentPlayerIt["trainer"] == "no";
		float x = currentPlayerIt["x"];
		float y = currentPlayerIt["y"];
		x *= 32;
		y *= 32;


		std::shared_ptr<Object> pnj = std::make_shared<Object>();
		auto sprite = pnj->AddComponent<C_Sprite>();
		sprite->SetTextureAllocator(&textureAllocator);
		sprite->SetSortOrder(sortOrder);
		sprite->SetScale(scale, scale);
		pnj->transform->SetPositionPNJ(x, y);


		auto c_pnj = pnj->AddComponent<C_pnj>();
		c_pnj->SetOldPosition(x, y);
		c_pnj->SetCollider(&collider);
		c_pnj->SetSpritePtr(sprite);

		if (style == "moving") {
			auto strings = currentPlayerIt["moves"];
			std::vector<std::string> vectorStrings;
			for (auto itStrings = strings.begin(); itStrings != strings.end(); itStrings++)
				vectorStrings.push_back(*itStrings);
			c_pnj->SetBehavior(style, vectorStrings);
		}
		else
			c_pnj->SetBehavior(style);


		auto animation = pnj->AddComponent<C_Animation>();

		loadAnimations(moves, animation, TextureID, offset);

		objects.Add(pnj);
		collider.Add(x, y, 5);
	}
	__int64 loadedPNJs = players.end() - players.begin();

	std::string pnjSTr = (loadedPNJs == 1) ? " PNJ" : " PNJs";

	Logger::info(className, __func__, "Successfully loaded " + std::to_string(loadedPNJs) + pnjSTr);
}