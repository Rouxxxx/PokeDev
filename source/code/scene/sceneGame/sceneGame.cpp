#include "sceneGame.h"

using json = nlohmann::json;

SceneGame::SceneGame(WorkingDirectory& workingDir, ResourceAllocator<sf::Texture>& textureAllocator, Window& window)
	: workingDir(workingDir), textureAllocator(textureAllocator), mapParser(textureAllocator), window(window), collider(Collider()) 
{}

void SceneGame::initTextClass(std::string path) {
	std::ifstream f(path);
	json data = json::parse(f);

	auto& meta = data["font"]["meta"];
	auto& colors = data["font"]["colors"];

	int size = meta["size"];
	int opacityShadow = meta["opacityShadow"];
	std::string file = meta["file"];
	std::string fileShadow = meta["fileShadow"];

	textClass = TextClass(colors, std::make_pair(file, fileShadow), opacityShadow, size);
}

FacingDirection findFacingDirection(std::string str) {
	std::vector<std::pair<std::string, FacingDirection>> table {
		{"idle", FacingDirection::Down},
		{"walkRight", FacingDirection::Right},
		{"walkLeft", FacingDirection::Left},
		{"walkUp", FacingDirection::Up},
		{"walkDown", FacingDirection::Down},
		{"runRight", FacingDirection::Right},
		{"runLeft", FacingDirection::Left},
		{"runUp", FacingDirection::Up},
		{"Down", FacingDirection::Down},
	};

	for (auto curr : table)
		if (curr.first == str)
			return curr.second;
	return FacingDirection::Down;
}

AnimationState findAnimationState(std::string str) {
	std::vector<std::pair<std::string, AnimationState>> table{
		{"idle", AnimationState::Idle},
		{"walkRight", AnimationState::WalkRight},
		{"walkLeft", AnimationState::WalkLeft},
		{"walkUp", AnimationState::WalkUp},
		{"walkDown", AnimationState::WalkDown},
		{"runRight", AnimationState::RunRight},
		{"runLeft", AnimationState::RunLeft},
		{"runUp", AnimationState::RunUp},
		{"Down", AnimationState::RunDown},
		{"idle", AnimationState::Idle},
		{"idleLeft", AnimationState::IdleLeft},
		{"idleRight", AnimationState::IdleRight},
		{"idleUp", AnimationState::IdleUp},
		{"idleDown", AnimationState::IdleDown}
	};

	for (auto curr : table)
		if (curr.first == str)
			return curr.second;
	return AnimationState::Idle;
}

std::shared_ptr < C_Transform> SceneGame::createPlayer() {
	std::ifstream f("resources/sprites/ethan/ethan.json");
	json data = json::parse(f);

	auto &meta = data["ethan"]["meta"];
	auto &frames = data["ethan"]["frames"];
	int sortOrder = meta["sortOrder"];

	std::string image = data["ethan"]["meta"]["image"];

	int TextureID = textureAllocator.add(workingDir.Get() + image);


	std::shared_ptr<Object> player = std::make_shared<Object>();
	auto sprite = player->AddComponent<C_Sprite>();
	sprite->SetTextureAllocator(&textureAllocator);
	sprite->SetSortOrder(sortOrder);
	sprite->SetScale(1.8f, 1.8f);
	unsigned int x = 15 * 32;
	unsigned int y = 9 * 32;
	player->transform->SetPosition(x, y - 8);

	auto movement = player->AddComponent<C_KeyboardMovement>();
	movement->SetInput(&input);
	movement->SetCollider(&collider);

	auto animation = player->AddComponent<C_Animation>();


	for (auto it = frames.begin(); it != frames.end(); it++) {
		std::string name = it.key();
		auto currentAnimIt = *it;

		AnimationState state = findAnimationState(name);
		FacingDirection face = findFacingDirection(name);

		std::shared_ptr<Animation> currentAnimation = std::make_shared<Animation>(face);

		for (auto it2 = currentAnimIt.begin(); it2 != currentAnimIt.end(); it2++) {
			auto currentFrameIt = *it2;
			float idleAnimSeconds = currentFrameIt["idleAnimSeconds"];
			int x = currentFrameIt["spriteSource"]["x"];
			int y = currentFrameIt["spriteSource"]["y"];
			int w = currentFrameIt["spriteSource"]["w"];
			int h = currentFrameIt["spriteSource"]["h"];
			currentAnimation->AddFrame(TextureID, x, y, w, h, idleAnimSeconds);
		}
		animation->AddAnimation(state, currentAnimation);
	}
	
	animation->SetAnimationState(Idle);

	auto camera = player->AddComponent<C_Camera>();
	camera->SetWindow(&window);
	sf::View view = window.GetView();
	view.zoom(0.45f);
	window.SetView(view);
	objects.Add(player);

	return player->transform;
}


void SceneGame::createTextBox(int id, std::shared_ptr<C_Transform> playerTransform) {
	std::shared_ptr<Object> textBox = std::make_shared<Object>();
	std::ifstream f("resources/sprites/textBox/textBox.json");
	json data = json::parse(f);

	auto& meta = data["textBox"]["meta"];
	std::string image = data["textBox"]["meta"]["image"];
	int sortOrder = meta["sortOrder"];
	float scale = data["textBox"]["meta"]["scale"];
	auto& boxes = data["textBox"]["boxes"];
	std::string str = meta["str"];

	auto sprite = textBox->AddComponent<C_Sprite_Popup>();
	sprite->SetTransform(playerTransform);
	sprite->SetTextureAllocator(&textureAllocator);
	sprite->SetSortOrder(sortOrder);
	sprite->SetScale(scale, scale);

	int TextureID = textureAllocator.add(workingDir.Get() + image);

	for (auto it = boxes.begin(); it != boxes.end(); it++) {
		int current = std::atoi(it.key().c_str());
		if (current == id) {
			auto currentFrameIt = *it;
			int x = currentFrameIt["x"];
			int y = currentFrameIt["y"];
			int w = currentFrameIt["w"];
			int h = currentFrameIt["h"];
			sprite->SetTextureRect(x, y, w, h);
			break;
		}
	}

	sprite->Load(TextureID);
	sprite->SetVectorString(window.GetView().getSize());
	sprite->SetStrToPrint(str);
	sprite->SetFonts(textClass.getFonts());
	sprite->SetSize(textClass.getSize());
	sprite->SetColor(textClass.getColor(textColor::Default));
	objects.Add(textBox);
}

void SceneGame::OnCreate()
{
	initTextClass("resources/font/font.json");
	sf::Vector2i mapOffset(16, 0);
	std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse(workingDir.Get() + "resources/map/Bourg Geon CSV.tmx", mapOffset, &collider);
	objects.Add(levelTiles);

	auto transform = createPlayer();
	createTextBox(1, transform);
}

void SceneGame::OnDestroy()
{}
void SceneGame::ProcessInput() {
	input.Update();
}

void SceneGame::Update(float deltaTime) {
	objects.ProcessRemovals();
	objects.ProcessNewObjects();
	objects.Update(deltaTime);
}

void SceneGame::LateUpdate(float deltaTime) {
	objects.LateUpdate(deltaTime);
}

void SceneGame::Draw(Window& window) {
	objects.Draw(window);
}

void SceneGame::InitPlayer() {
}