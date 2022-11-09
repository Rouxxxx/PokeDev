#include "../sceneGame.h"
#include "c_pnj.h"

void SceneGame::InitPNJs(reference players) {
	std::string filePath = "resources/sprites/trainers/trainers.json";
	std::ifstream f2(filePath);
	json data;
	try {
		data = json::parse(f2);
	}
	catch (...) {
		Logger::error(className, __func__, "couldn't load and parse " + filePath + ". No PNJ loaded");
		return;
	}
	auto& meta2 = data["trainers"]["meta"];
	auto moves = data["trainers"]["moves"];


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
	int loadedPNJs = 0;


	for (auto it = players.begin(); it != players.end(); it++) {
		auto currentPlayerIt = *it;
		int idPNJ = currentPlayerIt["id"];

		if (idPNJ >= width * height) {
			Logger::error(className, __func__, "couldn't load PNJ with id " + std::to_string(idPNJ) + ". Skipping");
			continue;
		}

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
		pnj->SetTextBox(textBoxPtr);
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
			auto waits = currentPlayerIt["waits"];
			std::vector<std::string> vectorStrings;
			std::vector<float> vectorWaits;
			
			for (auto itStrings = strings.begin() ; itStrings != strings.end(); itStrings++)
				vectorStrings.push_back(*itStrings);
			for (auto itWaits = waits.begin();itWaits != waits.end(); itWaits++)
				vectorWaits.push_back(*itWaits);

			if (vectorStrings.size() != vectorWaits.size())
				Logger::error(className, __func__, "waiting times and functions don't have the same size");
			c_pnj->SetBehavior(style, vectorStrings, vectorWaits);
		}
		else
			c_pnj->SetBehavior(style);


		auto animation = pnj->AddComponent<C_Animation>();

		loadAnimations(moves, animation, TextureID, offset);

		objects.Add(pnj);
		collider.Add(x, y, pnj);
		loadedPNJs++;
	}

	std::string pnjSTr = (loadedPNJs == 1) ? " PNJ" : " PNJs";

	Logger::info(className, __func__, "Successfully loaded " + std::to_string(loadedPNJs) + pnjSTr);
}