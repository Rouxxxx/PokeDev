#include "input.h"

Input::Input() 
{}

bool Input::IsKeyPressed(Key keycode)
{
	return thisFrameKeys.GetBit((int)keycode);
}
bool Input::IsKeyDown(Key keycode)
{
	bool lastFrame = lastFrameKeys.GetBit((int)keycode);
	bool thisFrame = thisFrameKeys.GetBit((int)keycode);
	return thisFrame && !lastFrame;
}
bool Input::IsKeyUp(Key keycode)
{
	bool lastFrame = lastFrameKeys.GetBit((int)keycode);
	bool thisFrame = thisFrameKeys.GetBit((int)keycode);
	return !thisFrame && lastFrame;
}


bool checkKeysPressed(std::vector<sf::Keyboard::Key>::iterator itBegin, std::vector<sf::Keyboard::Key>::iterator itEnd) {
	for (auto it = itBegin; it != itEnd; it++) {
		if (sf::Keyboard::isKeyPressed(*it))
			return true;
	}
	return false;
}


void Input::Update()
{
	lastFrameKeys.SetMask(thisFrameKeys);

	for (auto it = keysMapping.begin(); it != keysMapping.end(); it++) {
		bool isAnyKeyPressed = checkKeysPressed(it->second.begin(), it->second.end());
		thisFrameKeys.SetBit((int) it->first, isAnyKeyPressed);
	}
	/*thisFrameKeys.SetBit((int)Key::Left,
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)));
	thisFrameKeys.SetBit((int)Key::Right,
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::D)));
	thisFrameKeys.SetBit((int)Key::Up,
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)));
	thisFrameKeys.SetBit((int)Key::Down,
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::S)));
	thisFrameKeys.SetBit((int)Key::Esc),
		sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);*/
}

bool Input::isDirectionKeyPressed() {
	return IsKeyPressed(Key::Left) || IsKeyPressed(Key::Right) || IsKeyPressed(Key::Up) || IsKeyPressed(Key::Down);
}