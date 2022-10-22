#include <string>
#include <iostream>
#include "tileMapParser.h"

TileMapParser::TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator)
	: textureAllocator(textureAllocator) 
{}

std::vector<std::shared_ptr<Object>> TileMapParser::Parse(const std::string& file, sf::Vector2i offset, Collider* collider) {
	//std::cout << file << "\n";
	//struct stat buffer;
	//std::cout << (stat(file.c_str(), &buffer) == 0) << "\n";

	char* fileLoc = new char[file.size() + 1];
	//TODO: make multi format version of string copy
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, file.size() + 1, file.c_str());
#endif 
	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("map");

	// Loads tile layers from XML.
	std::pair<std::shared_ptr<MapTiles>, std::shared_ptr<TileSheets>> pair = BuildMapTiles(rootNode);
	std::shared_ptr<MapTiles> tiles = pair.first;

	std::pair<int, int> collisionsGid = findCollisionsGid(pair.second);

	// We need these to calculate the tiles position in world space
	int tileSizeX = std::atoi(rootNode->first_attribute("tilewidth")->value());
	int tileSizeY = std::atoi(rootNode->first_attribute("tileheight")->value());
	int mapsizeX = std::atoi(rootNode->first_attribute("width")->value());
	int mapsizeY = std::atoi(rootNode->first_attribute("height")->value());

	// This will contain all of our tiles as objects.
	std::vector<std::shared_ptr<Object>> tileObjects;

	// We iterate through each layer in the tile map
	for (const auto& layer : *tiles) {

		for (const auto& tile : *layer.second->layer) {

			std::shared_ptr<TileInfo> tileInfo = tile->properties;
			std::shared_ptr<Object> tileObject = std::make_shared<Object>();
			//TODO: tile scale should be set at the data level.
			const unsigned int tileScale = 1;

			if (layer.second->isVisible) {
				// Allocate sprite.
				auto sprite = tileObject->AddComponent<C_Sprite>();
				sprite->SetTextureAllocator(&textureAllocator);
				sprite->Load(tileInfo->textureID);
				sprite->SetTextureRect(tileInfo->textureRect);
				sprite->SetScale(tileScale, tileScale);
				sprite->SetSortOrder(layer.second->id);
			}

			// Calculate world position.
			unsigned int x = tile->x * tileSizeX * tileScale + offset.x;
			unsigned int y = tile->y * tileSizeY * tileScale + offset.y;

			int tileID = tileInfo->tileID;
			if (tileID >= collisionsGid.first && tileID <= collisionsGid.second)
				collider->Add((float)x, (float)y, tileID - collisionsGid.first);

			
			tileObject->transform->SetPosition(x, y);
			// Add new tile Object to the collection.
			tileObjects.emplace_back(tileObject);
		}
	}
	return tileObjects;
}

std::pair<std::shared_ptr<MapTiles>, std::shared_ptr<TileSheets>> TileMapParser::BuildMapTiles(xml_node<>* rootNode) {
	std::shared_ptr<TileSheets> tileSheetData = BuildTileSheetData(rootNode);
	std::shared_ptr<MapTiles> map = std::make_shared<MapTiles>();
	// We loop through each layer in the XML document.
	for (xml_node<>* node = rootNode->first_node("layer"); node; node = node->next_sibling()) {
		std::pair<std::string, std::shared_ptr<LayerStruct>> mapLayer = BuildLayer(node, tileSheetData);
		map->emplace(mapLayer);
	}
	return std::make_pair(map, tileSheetData);
}

std::pair<int, int> TileMapParser::findCollisionsGid(std::shared_ptr<TileSheets> tileSheets) {
	std::map<int, std::shared_ptr<TileSheetData>>::iterator it;

	for (it = tileSheets->begin(); it != tileSheets->end(); it++)
		if (it->second->name == "collisions") {
			int firstGid = it->first;
			return std::make_pair(it->first, it->first + it->second->tileCount);
		}
	return std::make_pair(-1, -1);

}

std::shared_ptr<TileSheets> TileMapParser::BuildTileSheetData(xml_node<>* rootNode) {
	std::map<int, std::shared_ptr<TileSheetData>> tileSheets;

	for (xml_node<>* tilesheetNode = rootNode->first_node("tileset"); tilesheetNode; tilesheetNode = tilesheetNode->next_sibling("tileset")) {
		TileSheetData tileSheetData;
		tileSheetData.name = tilesheetNode->first_attribute("name")->value();
		

		int firstid = std::atoi(tilesheetNode->first_attribute("firstgid")->value());
		tileSheetData.tileSize.x = std::atoi(tilesheetNode->first_attribute("tilewidth")->value());
		tileSheetData.tileSize.y = std::atoi(tilesheetNode->first_attribute("tileheight")->value());

		int tileCount = std::atoi(tilesheetNode->first_attribute("tilecount")->value());
		tileSheetData.tileCount = tileCount;
		tileSheetData.columns = std::atoi(tilesheetNode->first_attribute("columns")->value());
		tileSheetData.rows = tileCount / tileSheetData.columns;

		xml_node<>* imageNode = tilesheetNode->first_node("image");
		tileSheetData.textureId = textureAllocator.add("resources/sprites/" + std::string(imageNode->first_attribute("source")->value()));
		tileSheetData.imageSize.x = std::atoi(imageNode->first_attribute("width")->value());
		tileSheetData.imageSize.y = std::atoi(imageNode->first_attribute("height")->value());

		// We store the tile sheets firstid.
		tileSheets.insert(std::make_pair(firstid, std::make_shared<TileSheetData>(tileSheetData)));
	}
	return std::make_shared<TileSheets>(tileSheets);
}

std::pair<std::string, std::shared_ptr<LayerStruct>> TileMapParser::BuildLayer(xml_node<>* layerNode, std::shared_ptr<TileSheets> tileSheets)
{
    TileSet tileSet;
    std::shared_ptr<Layer> layer = std::make_shared<Layer>();

    
    int height = std::atoi(layerNode->first_attribute("height")->value());
	int width = std::atoi(layerNode->first_attribute("width")->value());
	int id = std::atoi(layerNode->first_attribute("id")->value());

    xml_node<>* dataNode = layerNode->first_node("data");
    char* mapIndices = dataNode->value();

    std::stringstream fileStream(mapIndices);

    int count = 0;

    std::string line;
    while (fileStream.good())
    {
        std::string substr;
        std::getline(fileStream, substr, ',');

        if (!Utilities::IsInteger(substr)) {
            substr.erase(std::remove(substr.begin(), substr.end(), '\r'), substr.end());
            substr.erase(std::remove(substr.begin(), substr.end(), '\n'), substr.end());

        }

        int tileId = std::stoi(substr);

        if (tileId != 0)
        {
            auto itr = tileSet.find(tileId);
            if (itr == tileSet.end())
            {
                std::shared_ptr<TileSheetData> tileSheet;

                for (auto iter = tileSheets->rbegin(); iter != tileSheets->rend(); ++iter)
                {
                    if (tileId >= iter->first) {
                        // We know the tile belongs to this tileset.
                        tileSheet = iter->second;
                        break;
                    }
                }

                if (!tileSheet)
                    //TODO: output error message.
                    continue;

                int textureX = tileId % tileSheet->columns - 1;
                int textureY = tileId / tileSheet->columns;

                std::shared_ptr<TileInfo> tileInfo = std::make_shared<TileInfo>(tileSheet->textureId, tileId, sf::IntRect(textureX * tileSheet->tileSize.x, textureY * tileSheet->tileSize.y, tileSheet->tileSize.x, tileSheet->tileSize.y));

                itr = tileSet.insert(std::make_pair(tileId, tileInfo)).first;
            }

            std::shared_ptr<Tile> tile = std::make_shared<Tile>();

            // Bind properties of a tile from a set.
            tile->properties = itr->second;
            tile->x = count % width - 1;
            tile->y = count / width;


            layer->emplace_back(tile);
        }
        count++;
    }

	std::shared_ptr<LayerStruct> layerStruct = std::make_shared<LayerStruct>();
	xml_attribute<>* visibleAttribute = layerNode->first_attribute("visible");
	if (visibleAttribute)
		layerStruct->isVisible = std::stoi(visibleAttribute->value());

	layerStruct->id = id;
	layerStruct->layer = layer;

    const std::string layerName = layerNode->first_attribute("name")->value();
    return std::make_pair(layerName, layerStruct);
}
