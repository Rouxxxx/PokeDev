#include "sceneGame.h"

using json = nlohmann::json;

SceneGame::SceneGame(WorkingDirectory& workingDir, ResourceAllocator<sf::Texture>& textureAllocator)
	: workingDir(workingDir), textureAllocator(textureAllocator), mapParser(textureAllocator), collider(Collider())
{}

void SceneGame::createPlayer() {

	std::ifstream f("resources/sprites/ethan/ethan.json");
	json data = json::parse(f);

	auto &meta = data["ethan"]["meta"];
	auto &frames = data["ethan"]["frames"];
	auto &states = data["ethan"]["states"];
	int sortOrder = meta["sortOrder"];


	std::string image = data["ethan"]["meta"]["image"];
	int TextureID = textureAllocator.add(workingDir.Get() + image);


	std::shared_ptr<Object> player = std::make_shared<Object>();
	auto sprite = player->AddComponent<C_Sprite>();
	sprite->SetTextureAllocator(&textureAllocator);
	sprite->SetSortOrder(sortOrder);
	unsigned int x = 23 * 32;
	unsigned int y = 9 * 32;
	player->transform->SetPosition(x, y);

	auto movement = player->AddComponent<C_KeyboardMovement>();
	movement->SetInput(&input);
	movement->SetCollider(&collider);

	auto animation = player->AddComponent<C_Animation>();


	for (auto it = frames.begin(); it != frames.end(); it++) {
		std::string name = it.key();
		auto currentAnimIt = *it;

		AnimationState state = AnimationState::Idle;

		for (auto itState = states.begin(); itState != states.end(); itState++) {
			if (*itState == name) {
				state = static_cast<AnimationState>(itState - states.begin());
				break;
			}
		}

		std::shared_ptr<Animation> currentAnimation = std::make_shared<Animation>(FacingDirection::Down);

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
	
	objects.Add(player);
}

void SceneGame::OnCreate()
{
	sf::Vector2i mapOffset(0, 0);
	std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse(workingDir.Get() + "resources/map/Bourg Geon CSV.tmx", mapOffset, &collider);
	objects.Add(levelTiles);

	createPlayer();
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

