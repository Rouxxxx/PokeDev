#include "c_sprite.h"
#include "../object/object.h"

C_Sprite::C_Sprite(Object* owner) 
	: Component(owner), currentTextureID(-1), allocator(nullptr)
{}
void C_Sprite::Load(int id)
{
	// Check its not already our current texture.
	if (id == 0 || id == currentTextureID)
		return;

	currentTextureID = id;
	std::shared_ptr<sf::Texture> texture = allocator->get(id);
	sprite.setTexture(*texture);
}

void C_Sprite::Load(const std::string& filePath) {
	if (!allocator)
		return;

	int textureID = allocator->add(filePath);
	// Check its not already our current texture.
	if (textureID >= 0 && textureID != currentTextureID) {
		currentTextureID = textureID;
		std::shared_ptr<sf::Texture> texture = allocator->get(textureID);
		sprite.setTexture(*texture);
	}
}
void C_Sprite::SetTextureRect(int x, int y, int width, int height) {
	sprite.setTextureRect(sf::IntRect(x, y, width, height));
}
void C_Sprite::SetTextureRect(const sf::IntRect& rect) {
	sprite.setTextureRect(rect);
}


void C_Sprite::SetTextureAllocator(ResourceAllocator<sf::Texture>* allocator) {
	this->allocator = allocator;
}

bool C_Sprite::IsInWindow() {
	sf::Vector2f pos = sprite.getPosition();
	float centreX = Config::windowCentreX;
	float centreY = Config::windowCentreY;

	float sizeX = Config::windowSizeX;
	float sizeY = Config::windowSizeY;

	float xMax = centreX + sizeX / 2;
	float yMax = centreY + sizeY / 2;

	float xMin = centreX - sizeX / 2;
	float yMin = centreY - sizeY / 2;
	if (pos.x < (xMin - 32) || pos.x > xMax)
		return false;
	if (pos.y < (yMin - 32) || pos.y > yMax)
		return false;

	return true;
}


void C_Sprite::Draw(Window& window) {
	if (IsInWindow())
		window.Draw(sprite);
}

void C_Sprite::LateUpdate(float deltaTime) {
	sprite.setPosition(owner->transform->GetPosition());
}

void C_Sprite::SetScale(float scaleX, float scaleY) {
	sprite.setScale(scaleX, scaleY);
}