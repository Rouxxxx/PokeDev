#include "c_textbox.h"
#include "../../object/object.h"

C_TextBox::C_TextBox(Object* owner)
	: Component(owner), currentTextureID(-1), allocator(nullptr), playerTransform(nullptr), currentState(sf::Text()), currentStateShadow(sf::Text()) {
	currentState.setPosition(100.0f, 200.0f);
}
void C_TextBox::Load(int id) {
	if (id == 0 || id == currentTextureID)
		return;

	currentTextureID = id;
	std::shared_ptr<sf::Texture> texture = allocator->get(id);
	sprite.setTexture(*texture);
}

void C_TextBox::Load(const std::string& filePath) {
	if (!allocator)
		return;

	int textureID = allocator->add(filePath);

	if (textureID >= 0 && textureID != currentTextureID) {
		currentTextureID = textureID;
		std::shared_ptr<sf::Texture> texture = allocator->get(textureID);
		sprite.setTexture(*texture);
	}
}
void C_TextBox::SetTextureRect(int x, int y, int width, int height) {
	sprite.setTextureRect(sf::IntRect(x, y, width, height));
}
void C_TextBox::SetTextureRect(const sf::IntRect& rect) {
	sprite.setTextureRect(rect);
}


void C_TextBox::SetTextureAllocator(ResourceAllocator<sf::Texture>* allocator) {
	this->allocator = allocator;
}
void C_TextBox::SetTransform(std::shared_ptr<C_Transform> transform) {
	this->playerTransform = transform;
}


void C_TextBox::Draw(Window& window) {
	window.Draw(sprite);
	window.Draw(currentStateShadow);
	window.Draw(currentState);

	auto cursor = owner->GetTextBox();
	if (isDone)
		cursor->Draw(window);
}

void C_TextBox::UpdateRects() {
	sf::Vector2f vec = playerTransform->GetPosition();

	vec.y += vectorString.y;
	vec.x -= vectorString.x;
	owner->transform->SetPosition(vec);

	sf::Vector2f vecStr = vec + sf::Vector2f(25, 7);
	currentState.setPosition(vecStr);
	currentStateShadow.setPosition(vecStr);

	sprite.setPosition(vec);

	auto cursor = owner->GetTextBox();
	if (cursor) {
		sf::Vector2f vecCursor = vec + sf::Vector2f(425, 45);
		cursor->transform->SetPosition(vecCursor);
	}
}

void C_TextBox::UpdateStrings() {
	std::string newString = currentState.getString();

	isDone = (newString == stringToPrint);
	if (isDone) 
		return;
	char at = stringToPrint.at(newString.size());
	newString += at;
	currentState.setString(newString);
	currentStateShadow.setString(newString);
}

void C_TextBox::LateUpdate(float deltaTime) {
	UpdateRects();
	UpdateStrings();

	auto cursor = owner->GetTextBox();
	if (isDone) {
		cursor->Update(deltaTime);
		cursor->LateUpdate(deltaTime);
	}
}

void C_TextBox::SetScale(float scaleX, float scaleY) {
	sprite.setScale(scaleX, scaleY);
}


void C_TextBox::SetFonts(std::pair<sf::Font, sf::Font> newFonts) {
	fonts = newFonts;
	currentState.setFont(fonts.first);
	currentStateShadow.setFont(fonts.second);
}

void C_TextBox::SetStrToPrint(std::string str) {
	Reset();
	stringToPrint = str;
}
void C_TextBox::SetVectorString(sf::Vector2f vec) {
	sf::Vector2f newVec;
	newVec.y = (vec.y / 2) - 85;
	newVec.x = (vec.x / 2) - 5;
	vectorString = newVec;
}

void C_TextBox::SetSize(int size) {
	currentState.setCharacterSize(size);
	currentStateShadow.setCharacterSize(size);
}

void C_TextBox::SetColor(std::pair<sf::Color, sf::Color> colors) {
	currentState.setFillColor(colors.first);
	currentStateShadow.setFillColor(colors.second);
}

void C_TextBox::Reset() {
	currentState.setString("");
	currentStateShadow.setString("");
	owner->SetOff();
}

bool C_TextBox::IsDone() { return isDone; }