#include "../sceneGame.h"

void SceneGame::InitTextClass(std::string path) {
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


void SceneGame::createTextBox(int id, std::shared_ptr<C_Transform> playerTransform) {
	textBoxPtr = std::make_shared<Object>();
	textBoxPtr->SetOff();
	std::ifstream f("resources/sprites/textBox/textBox.json");
	json data = json::parse(f);

	auto& meta = data["textBox"]["meta"];
	std::string image = data["textBox"]["meta"]["image"];
	int sortOrder = meta["sortOrder"];
	float scale = data["textBox"]["meta"]["scale"];
	auto& boxes = data["textBox"]["boxes"];
	std::string str = meta["str"];

	basicWidth = meta["cursorWidth"];
	basicHeight = meta["cursorHeight"];

	auto sprite = textBoxPtr->AddComponent<C_TextBox>();
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
	objects.Add(textBoxPtr);

	createTextBoxCursor(TextureID, sortOrder, scale, data["textBox"]["animation"]);

	textBoxPtr->SetTextBox(std::make_shared<Object>(cursor));
}

void SceneGame::createTextBoxCursor(int TextureID, int sortOrder, float scale, reference frames) {
	cursor = Object();
	auto spriteCursor = cursor.AddComponent<C_Sprite>();
	spriteCursor->SetTextureAllocator(&textureAllocator);
	spriteCursor->SetSortOrder(sortOrder + 1);
	spriteCursor->SetScale(scale / 4, scale / 4);
	spriteCursor->Load(TextureID);

	auto animation = cursor.AddComponent<C_Animation>();
	loadAnimations(frames, animation, TextureID);
	animation->SetAnimationState(WalkDown);
	cursor.Awake();
	cursor.Start();
}