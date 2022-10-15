#pragma once
#include "component.h"
#include "c_transform.h"
#include "../resource/resourceAllocator.h"


class C_Sprite : public Component
{
public:
	C_Sprite(Object* owner);
	// Loads a sprite from file.
	void Load(const std::string& filePath);
	void Load(int id); 
	void SetTextureAllocator(ResourceAllocator<sf::Texture>* allocator);

	// We override the draw method so we can draw our sprite.
	void Draw(Window& window) override;
	void LateUpdate(float deltaTime) override;
private:
	ResourceAllocator<sf::Texture>* allocator;
	sf::Sprite sprite;

};
