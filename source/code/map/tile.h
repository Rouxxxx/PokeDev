#pragma once

#include <SFML/Graphics.hpp>
#include "../resource/resourceAllocator.h"

// Stores common tile data.
struct TileInfo
{
	TileInfo() 
		: tileID(-1), textureID(-1)
	{}
	TileInfo(int textureID, unsigned int tileID, sf::IntRect textureRect)
		: textureID(textureID), tileID(tileID), textureRect(textureRect) { }
	int tileID;
	int textureID;
	sf::IntRect textureRect;
};

struct Tile {
	std::shared_ptr<TileInfo> properties;
	int x;
	int y;
};
