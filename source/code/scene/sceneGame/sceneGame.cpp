#include "sceneGame.h"

using json = nlohmann::json;

SceneGame::SceneGame(WorkingDirectory& workingDir, ResourceAllocator<sf::Texture>& textureAllocator, Window& window)
	: workingDir(workingDir), textureAllocator(textureAllocator), mapParser(textureAllocator), window(window), collider(Collider()), className(typeid(this).name())
{}

void SceneGame::loadAnimations(reference frames, std::shared_ptr<C_Animation> animation, int TextureID) {
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
}

void SceneGame::OnCreate()
{
	InitTextClass("resources/font/font.json");
	InitMap("resources/map/Bourg_Geon/Bourg_Geon.json");

	auto transform = createPlayer();
	//createTextBox(1, transform);
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