#include "c_sprite.h"
#include "../object/object.h"

C_Sprite::C_Sprite(Object* owner) : 
	Component(owner), allocator(nullptr)
{}

void C_Sprite::SetTextureAllocator(ResourceAllocator<sf::Texture>* allocator) {
	this->allocator = allocator;
}

void C_Sprite::Load(int id) {
	if (id >= 0) {
		std::shared_ptr<sf::Texture> texture = allocator->get(id);
		sprite.setTexture(*texture);
	}
}
void C_Sprite::Load(const std::string& filePath) {
	if (allocator) {
		int textureID = allocator->add(filePath);
		if (textureID >= 0) {
			std::shared_ptr<sf::Texture> texture = allocator->get(textureID);
			sprite.setTexture(*texture);
		}
	}
}


void C_Sprite::Draw(Window& window) {
	window.Draw(sprite);
}

void C_Sprite::LateUpdate(float deltaTime) {
	sprite.setPosition(owner->transform->GetPosition());
}
