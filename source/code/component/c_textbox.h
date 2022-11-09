#pragma once
#include "component.h"
#include "c_transform.h"
#include "c_Drawable.h"

#include "../resource/resourceAllocator.h"

class C_TextBox : public Component, public C_Drawable
{
public:
	C_TextBox(Object* owner);
	// Loads a sprite from file.
	void Load(const std::string& filePath);
	void Load(int id);
	void SetTextureAllocator(ResourceAllocator<sf::Texture>* allocator);

	// We override the draw method so we can draw our sprite.
	void Draw(Window& window) override;
	void UpdateRects();
	void UpdateStrings();
	void LateUpdate(float deltaTime) override;

	void SetTextureRect(int x, int y, int width, int height);
	void SetTextureRect(const sf::IntRect& rect);
	void SetTransform(std::shared_ptr<C_Transform> transform);
	void SetScale(float scaleX, float scaleY);

	void SetFonts(std::pair<sf::Font, sf::Font> newFonts);
	void SetStrToPrint(std::string strToPrint);
	void SetVectorString(sf::Vector2f vec);
	void SetSize(int size);
	void SetColor(std::pair<sf::Color, sf::Color> colors);

	void Reset();

private:
	std::shared_ptr<C_Transform> playerTransform;
	ResourceAllocator<sf::Texture>* allocator;
	sf::Sprite sprite;
	int currentTextureID;
	std::string stringToPrint;
	std::pair<sf::Font, sf::Font> fonts;
	sf::Text currentState;
	sf::Text currentStateShadow;
	sf::Vector2f vectorString;
};
