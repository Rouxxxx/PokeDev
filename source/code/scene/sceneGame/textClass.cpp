#include "textClass.h"

textColor strToColor(std::string color) {
	std::vector<std::pair<std::string, textColor>> table {
		{"Default", textColor::Default}
	};

	for (auto curr : table)
		if (curr.first == color)
			return curr.second;
	return textColor::Default;
}

sf::Color hexToColor(std::string hex) {
	int r, g, b;
	int res = sscanf_s(hex.c_str(), "%02x%02x%02x", &r, &g, &b);

	return sf::Color(r, g, b);
}

TextClass::TextClass()
	: size(0)
{}

TextClass::TextClass(reference colors, std::pair<std::string, std::string> fontsStr, int opacity, int size)
	: size(size) {

	fonts.first.loadFromFile(fontsStr.first);
	fonts.second.loadFromFile(fontsStr.second);

	for (auto it = colors.begin(); it != colors.end(); it++) {
		auto currentColor = (*it);
		std::string name = it.key();

		std::string color = currentColor["color"];
		std::string colorShadow = currentColor["colorShadow"];
		
		sf::Color colorObject = hexToColor(color);
		sf::Color colorObjectShadow = hexToColor(colorShadow);
		colorObjectShadow.a = opacity;

		textColor textColor = strToColor(name);

		setColor(textColor, colorObject, colorObjectShadow);
	}
}

void TextClass::setColor(textColor textColor, sf::Color color, sf::Color colorShadow) {
	map.emplace(textColor, std::make_pair(color, colorShadow));
}

std::pair<sf::Color, sf::Color> TextClass::getColor(textColor color) {
	auto it = map.find(color);
	return (it != map.end()) ? it->second : std::make_pair(sf::Color(), sf::Color());
}

std::pair<sf::Font, sf::Font> TextClass::getFonts() {
	return fonts;
}

int TextClass::getSize() {
	return size;
}