#pragma once

#include<fstream>
#include "../../utils/json/json.hpp"

#include "../scene.h"
#include "../../windowManager/input.h"
#include "../../utils/workingDirectory.h"

#include "../../object/object.h"
#include "../../object/objectCollection.h"

#include "../../component/c_sprite.h"
#include  "../../component/c_keyboardMovement.h"

#include "../../resource/resourceAllocator.h"

#include "../../map/tileMapParser.h"

class SceneGame : public Scene
{
public:
	SceneGame(WorkingDirectory& workingDir, ResourceAllocator<sf::Texture>& textureAllocator);
	void createPlayer();
	void OnCreate() override;
	void OnDestroy() override;
	void ProcessInput() override;
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
	void Draw(Window& window) override;
	
private:
	ResourceAllocator<sf::Texture>& textureAllocator;
	ObjectCollection objects;
	WorkingDirectory& workingDir;
	Input input;
	TileMapParser mapParser;
	Collider collider;
};
