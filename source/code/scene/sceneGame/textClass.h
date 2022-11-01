#pragma once

#include <map>
#include <SFML/Graphics.hpp>

#include "../../utils/json/json.hpp"

using json = nlohmann::json;
using reference = const nlohmann::json&;

enum textColor {
	Default
};

class TextClass {
public:
	TextClass();
	TextClass(reference colors, std::pair<std::string, std::string> fonts, int opacity, int size);
	void setColor(textColor, sf::Color, sf::Color);
	std::pair<sf::Color, sf::Color> getColor(textColor);
	std::pair<sf::Font, sf::Font> getFonts();
	int getSize();
private:
	int size;
	std::pair<sf::Font, sf::Font> fonts;
	std::map<textColor, std::pair<sf::Color, sf::Color>> map;
};