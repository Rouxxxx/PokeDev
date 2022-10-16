#include "sceneGame.h"
#include "../../component/c_animation.h"

SceneGame::SceneGame(WorkingDirectory& workingDir, ResourceAllocator<sf::Texture>& textureAllocator)
	: workingDir(workingDir), textureAllocator(textureAllocator)
{}

void SceneGame::OnCreate()
{
	std::shared_ptr<Object> player = std::make_shared<Object>();
	auto sprite = player->AddComponent<C_Sprite>();
	sprite->SetTextureAllocator(&textureAllocator);

	auto movement = player->AddComponent<C_KeyboardMovement>();
	movement->SetInput(&input);

	auto animation = player->AddComponent<C_Animation>();
	int TextureID = textureAllocator.add(workingDir.Get() + "../sprites/ethan.png");
	const int frameWidth = 17;
	const int frameHeight = 25;
	const float idleAnimFrameSeconds = 1.0f;

	std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>(FacingDirection::Down);
	idleAnimation->AddFrame(TextureID, 7, 5, frameWidth, frameHeight, idleAnimFrameSeconds);
	animation->AddAnimation(AnimationState::Idle, idleAnimation);

	std::shared_ptr<Animation> walkDown = std::make_shared<Animation>(FacingDirection::Down);

	walkDown->AddFrame(TextureID, 26, 5, frameWidth, frameHeight, idleAnimFrameSeconds);
	walkDown->AddFrame(TextureID, 7, 5, frameWidth, frameHeight, idleAnimFrameSeconds);
	walkDown->AddFrame(TextureID, 45, 5, frameWidth, frameHeight, idleAnimFrameSeconds);
	animation->AddAnimation(AnimationState::WalkDown, walkDown);

	const float walkAnimFrameSeconds = 0.20f;
	const int frameWalkWidth = 20;
	const int frameWalkWeight = 23;
	std::shared_ptr<Animation> walkAnimationLeft = std::make_shared<Animation>(FacingDirection::Right);
	walkAnimationLeft->AddFrame(TextureID, 26, 34, 20, frameHeight, walkAnimFrameSeconds);
	walkAnimationLeft->AddFrame(TextureID, 5, 33, 22, 24, walkAnimFrameSeconds);
	walkAnimationLeft->AddFrame(TextureID, 47, 34, frameWidth, frameHeight, walkAnimFrameSeconds);
	animation->AddAnimation(AnimationState::WalkLeft, walkAnimationLeft);

	std::shared_ptr<Animation> walkAnimationRight = std::make_shared<Animation>(FacingDirection::Left);
	walkAnimationRight->AddFrame(TextureID, 20, 89, frameWidth, frameHeight, walkAnimFrameSeconds);
	walkAnimationRight->AddFrame(TextureID, 5, 89, 19, 24, walkAnimFrameSeconds);
	walkAnimationRight->AddFrame(TextureID, 44, 89, frameWidth, frameHeight, walkAnimFrameSeconds);
	animation->AddAnimation(AnimationState::WalkRight, walkAnimationRight);

	objects.Add(player);
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
