#include "../sceneGame.h"
#include "c_pnj.h"

void SceneGame::InitPNJs(reference players) {
	std::ifstream f2("resources/sprites/trainers/trainers.json");
	json data2 = json::parse(f2);
	auto& meta2 = data2["trainers"]["meta"];
	auto trainersList = data2["trainers"]["trainersList"];

	int sortOrder = meta2["sortOrder"];
	float scale = meta2["scale"];
	std::string image = meta2["image"];
	int TextureID = textureAllocator.add(workingDir.Get() + image);

	int loadedPNJs = 0;


	for (auto it = players.begin(); it != players.end(); it++) {
		auto currentPlayerIt = *it;
		int idPNJ = currentPlayerIt["id"];

		int idTrainer = 0;

		for (auto itTrainer = trainersList.begin(); itTrainer != trainersList.end(); itTrainer++) {
			idTrainer++;

			if (idPNJ != idTrainer)
				continue;

			std::string style = currentPlayerIt["style"];

			bool isTrainer = currentPlayerIt["trainer"] == "no";
			int x = currentPlayerIt["x"];
			int y = currentPlayerIt["y"];
			x *= 32;
			y *= 32;

			std::shared_ptr<Object> pnj = std::make_shared<Object>();
			auto sprite = pnj->AddComponent<C_Sprite>();
			sprite->SetTextureAllocator(&textureAllocator);
			sprite->SetSortOrder(sortOrder);
			sprite->SetScale(scale, scale);
			pnj->transform->SetPositionTrainer(x, y);

			auto c_pnj = pnj->AddComponent<C_pnj>();
			c_pnj->SetOldPosition(x, y);
			c_pnj->SetCollider(&collider);
			c_pnj->SetSpritePtr(sprite);
			c_pnj->SetBehavior(style);

			auto animation = pnj->AddComponent<C_Animation>();

			auto frames = *itTrainer;

			loadAnimations(frames, animation, TextureID);
			loadedPNJs++;

			objects.Add(pnj);
			collider.Add(x, y, 5);

			break;
		}
	}

	std::string pnjSTr = (loadedPNJs == 1) ? " PNJ" : " PNJs";

	Logger::info(className, __func__, "Successfully loaded " + std::to_string(loadedPNJs) + pnjSTr);
}