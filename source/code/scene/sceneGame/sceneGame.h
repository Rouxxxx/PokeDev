#pragma once

#include<fstream>

#include "../../utils/Logger/logger.h"
#include "../../utils/json/json.hpp"

#include "../scene.h"
#include "../../windowManager/c_camera.h"
#include "../../windowManager/input.h"
#include "../../utils/workingDirectory.h"

#include "../../object/object.h"
#include "../../object/objectCollection.h"

#include "../../component/c_sprite.h"
#include "../../component/c_sprite_popup.h"
#include  "player/c_keyboardMovement.h"

#include "../../resource/resourceAllocator.h"

#include "../../map/tileMapParser.h"

#include "textClass.h"

class SceneGame : public Scene
{
public:
	SceneGame(WorkingDirectory&, ResourceAllocator<sf::Texture>&, Window&);
	
	void OnCreate() override;
	void OnDestroy() override;
	void ProcessInput() override;
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
	void Draw(Window& window) override;
	
	
private:
	void InitPNJs(reference players);
	void InitMap(std::string path);
	void InitTextClass(std::string path);
	void InitPlayer();
	std::shared_ptr <C_Transform> createPlayer();
	void createTextBox(int id, std::shared_ptr<C_Transform>);
	void loadAnimations(reference frames, std::shared_ptr<C_Animation> animation, int TextureID, sf::Vector2i = sf::Vector2i());

	ResourceAllocator<sf::Texture>& textureAllocator;
	ObjectCollection objects;
	WorkingDirectory& workingDir;
	Input input;
	TileMapParser mapParser;
	Collider collider;
	Window& window;
	TextClass textClass;

	const std::string className;

	int pnjWidth;
	int pnjHeight;
};

inline FacingDirection findFacingDirection(std::string str) {
	std::vector<std::pair<std::string, FacingDirection>> table{
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


inline AnimationState findAnimationState(std::string str) {
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