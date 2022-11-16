#pragma once
#include "component.h"
#include "c_transform.h"
#include "c_Drawable.h"

#include "../resource/resourceAllocator.h"



class C_Sprite : public Component, public C_Drawable
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

	void SetTextureRect(int x, int y, int width, int height);
	void SetTextureRect(const sf::IntRect& rect);
	void SetScale(float scaleX, float scaleY);

private:
	bool IsInWindow();
	ResourceAllocator<sf::Texture>* allocator;
	sf::Sprite sprite;
	int currentTextureID; // We’ll now keep track of our currently set texture.
};
