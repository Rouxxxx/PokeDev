#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <sstream>

#include "../../utils/json/json.hpp"
#include "../utils/RapidXML/rapidxml.hpp"
#include "../utils/RapidXML/rapidxml_utils.hpp"

#include "tile.h"
#include "../utils/utilities.h"
#include "../object/object.h"
#include "../component/c_sprite.h"
#include "../component/c_animation.h"
#include "collider.h"

using namespace rapidxml;

using Layer = std::vector<std::shared_ptr<Tile>>;
// Stores layer names with layer.
// Stores the different tile types that can be used.
using TileSet = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>;


struct TileSheetData
{
	// The texture id will be retrieved by using our texture allocator.
	int textureId = 0; // The id of the tile sets texture. 
	sf::Vector2u imageSize; // The size of the texture.
	int columns = 0; // How many columns in the tile sheet.
	int rows = 0; // How many rows in the tile sheet.
	sf::Vector2u tileSize; // The size of an individual tile.
	std::string name;
	int tileCount = 0;
};

struct LayerStruct {
	int id = 0;
	bool isVisible = true;
	std::shared_ptr<Layer> layer = 0;
};

using MapTiles = std::map<std::string, std::shared_ptr<LayerStruct>>;

using TileSheets = std::map<int, std::shared_ptr<TileSheetData>>;

class TileMapParser
{
public:
	TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator);
	std::vector<std::shared_ptr<Object>> Parse(const std::string& file, sf::Vector2i offset, Collider* collider);
private:
	std::pair<int, int> findCollisionsGid(std::shared_ptr<TileSheets> tileSheets);
	std::shared_ptr<TileSheets> BuildTileSheetData(xml_node<>* rootNode);
	std::pair<std::string, std::shared_ptr<LayerStruct>> BuildLayer(xml_node<>* layerNode, std::shared_ptr<TileSheets> tileSheets);
	std::pair <std::shared_ptr<MapTiles>, std::shared_ptr<TileSheets>> BuildMapTiles(xml_node<>* rootNode);
	ResourceAllocator<sf::Texture>& textureAllocator;
};
