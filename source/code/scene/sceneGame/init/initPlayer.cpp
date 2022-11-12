#include "../sceneGame.h"

void SceneGame::createPlayer() {
	std::ifstream f("resources/sprites/ethan/ethan.json");
	json data = json::parse(f);

	auto& meta = data["ethan"]["meta"];
	auto& frames = data["ethan"]["frames"];
	int sortOrder = meta["sortOrder"];
	float scale = meta["scale"];

	std::string image = data["ethan"]["meta"]["image"];

	int TextureID = textureAllocator.add(workingDir.Get() + image);

	std::shared_ptr<Object> player = std::make_shared<Object>();
	auto sprite = player->AddComponent<C_Sprite>();
	sprite->SetTextureAllocator(&textureAllocator);
	sprite->SetSortOrder(sortOrder);
	sprite->SetScale(scale, scale);
	float x = 15 * 32;
	float y = 11 * 32;
	player->transform->SetPositionTrainer(x, y);

	auto movement = player->AddComponent<C_Keyboard>();
	movement->SetInput(&input);
	movement->SetCollider(&collider);
	collider.Add(x, y, player);
	movement->SetOldPosition(x, y);

	auto animation = player->AddComponent<C_Animation>();

	loadAnimations(frames, animation, TextureID);
	animation->SetAnimationState(Idle);

	auto camera = player->AddComponent<C_Camera>();
	camera->SetWindow(&window);
	sf::View view = window.GetView();
	view.zoom(0.45f);
	window.SetView(view);
	objects.Add(player);

	createTextBox(1, player->transform);
	player->SetTextBox(textBoxPtr);
}