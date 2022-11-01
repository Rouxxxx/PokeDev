#include "c_sprite_popup.h"
#include "../object/object.h"

C_Sprite_Popup::C_Sprite_Popup(Object* owner)
	: Component(owner), currentTextureID(-1), allocator(nullptr), playerTransform(nullptr), currentState(sf::Text()), currentStateShadow(sf::Text()) {
	currentState.setPosition(100.0f, 200.0f);
}
void C_Sprite_Popup::Load(int id) {
	if (id == 0 || id == currentTextureID)
		return;

	currentTextureID = id;
	std::shared_ptr<sf::Texture> texture = allocator->get(id);
	sprite.setTexture(*texture);
}

void C_Sprite_Popup::Load(const std::string& filePath) {
	if (!allocator)
		return;

	int textureID = allocator->add(filePath);

	if (textureID >= 0 && textureID != currentTextureID) {
		currentTextureID = textureID;
		std::shared_ptr<sf::Texture> texture = allocator->get(textureID);
		sprite.setTexture(*texture);
	}
}
void C_Sprite_Popup::SetTextureRect(int x, int y, int width, int height) {
	sprite.setTextureRect(sf::IntRect(x, y, width, height));
}
void C_Sprite_Popup::SetTextureRect(const sf::IntRect& rect) {
	sprite.setTextureRect(rect);
}


void C_Sprite_Popup::SetTextureAllocator(ResourceAllocator<sf::Texture>* allocator) {
	this->allocator = allocator;
}
void C_Sprite_Popup::SetTransform(std::shared_ptr<C_Transform> transform) {
	this->playerTransform = transform;
}


void C_Sprite_Popup::Draw(Window& window) {
	window.Draw(sprite);
	window.Draw(currentStateShadow);
	window.Draw(currentState);
}

void C_Sprite_Popup::UpdateRects() {
	sf::Vector2f vec = playerTransform->GetPosition();

	vec.y += vectorString.y;
	vec.x -= vectorString.x;
	owner->transform->SetPosition(vec);

	sf::Vector2f vecStr = vec + sf::Vector2f(25, 7);
	currentState.setPosition(vecStr);
	currentStateShadow.setPosition(vecStr);

	sprite.setPosition(vec);
}

void C_Sprite_Popup::UpdateStrings() {
	std::string newString = currentState.getString();

	if (newString == stringToPrint)
		return;
	char at = stringToPrint.at(newString.size());
	newString += at;
	currentState.setString(newString);
	currentStateShadow.setString(newString);
}

void C_Sprite_Popup::LateUpdate(float deltaTime) {
	UpdateRects();
	UpdateStrings();
}

void C_Sprite_Popup::SetScale(float scaleX, float scaleY) {
	sprite.setScale(scaleX, scaleY);
}


void C_Sprite_Popup::SetFonts(std::pair<sf::Font, sf::Font> newFonts) {
	fonts = newFonts;
	currentState.setFont(fonts.first);
	currentStateShadow.setFont(fonts.second);
}

void C_Sprite_Popup::SetStrToPrint(std::string str) {
	stringToPrint = str;
}
void C_Sprite_Popup::SetVectorString(sf::Vector2f vec) {
	sf::Vector2f newVec;
	newVec.y = (vec.y / 2) - 85;
	newVec.x = (vec.x / 2) - 5;
	vectorString = newVec;
}

void C_Sprite_Popup::SetSize(int size) {
	currentState.setCharacterSize(size);
	currentStateShadow.setCharacterSize(size);
}

void C_Sprite_Popup::SetColor(std::pair<sf::Color, sf::Color> colors) {
	currentState.setFillColor(colors.first);
	currentStateShadow.setFillColor(colors.second);
}