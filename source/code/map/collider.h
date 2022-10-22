#pragma once

#include <map>
#include <SFML/Graphics.hpp>


class Collider
{
public:
	Collider();
	void Add(float x, float y, int tileID);
	void Add(sf::Vector2f vec, int tileID);
	void Delete(float x, float y);
	void Delete(sf::Vector2f vec);

	int FindLeft(float x, float y);
	int FindLeft(sf::Vector2f vec);
	int FindRight(float x, float y);
	int FindRight(sf::Vector2f vec);
	int FindUp(float x, float y);
	int FindUp(sf::Vector2f vec);
	int FindDown(float x, float y);
	int FindDown(sf::Vector2f vec);
	int Find(float x, float y);
	int Find(sf::Vector2f vec);
	void Empty();
private:
	std::map<std::pair<float, float>, int> map;
};
