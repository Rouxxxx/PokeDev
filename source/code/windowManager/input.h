#pragma once
#include <SFML/Graphics.hpp>
#include "../../utils/json/json.hpp"

#include "../utils/bitMask.h"
#include "../../utils/Logger/logger.h"


using json = nlohmann::json;
using reference = const nlohmann::json&;

enum Key
{
	None = 0,
	Left = 1,
	Right = 2,
	Up = 3,
	Down = 4,
	Esc = 5,
	A = 6,
	B = 7,
	X = 8,
	Y = 9,
	Start = 10,
	Select = 11,
};

class Input
{
public:
	Input();
	void InitKeys(reference ref);
	bool IsKeyPressed(Key keycode); // if the key is pressed.
	bool IsKeyDown(Key keycode); // if the key was just pressed.
	bool IsKeyUp(Key keycode); // if the key was just released.

	void Update();
	bool isDirectionKeyPressed();

private:
	std::vector<std::pair<Key, std::vector<sf::Keyboard::Key>>> keysMapping;
	Bitmask thisFrameKeys;
	Bitmask lastFrameKeys;

};
