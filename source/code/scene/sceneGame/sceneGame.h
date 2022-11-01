#pragma once

#include<fstream>
#include "../../utils/json/json.hpp"

#include "../scene.h"
#include "../../windowManager/c_camera.h"
#include "../../windowManager/input.h"
#include "../../utils/workingDirectory.h"

#include "../../object/object.h"
#include "../../object/objectCollection.h"

#include "../../component/c_sprite.h"
#include "../../component/c_sprite_popup.h"
#include  "../../component/c_keyboardMovement.h"

#include "../../resource/resourceAllocator.h"

#include "../../map/tileMapParser.h"

#include "textClass.h"

class SceneGame : public Scene
{
public:
	SceneGame(WorkingDirectory& workingDir, ResourceAllocator<sf::Texture>& textureAllocator, Window& window);
	std::shared_ptr < C_Transform> createPlayer();
	void initTextClass(std::string path);
	void createTextBox(int id, std::shared_ptr<C_Transform> playerTransform);
	void OnCreate() override;
	void OnDestroy() override;
	void ProcessInput() override;
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
	void Draw(Window& window) override;
	void InitPlayer();
	
private:
	ResourceAllocator<sf::Texture>& textureAllocator;
	ObjectCollection objects;
	WorkingDirectory& workingDir;
	Input input;
	TileMapParser mapParser;
	Collider collider;
	Window& window;
	TextClass textClass;
};
