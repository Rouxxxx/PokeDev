#include "c_Transform.h"

C_Transform::C_Transform(Object* owner)
	: Component(owner), position(0.f, 0.f)
{ }


void C_Transform::SetPositionTrainer(float x, float y) {
	position.x = x;
	position.y = y - 8;
}
void C_Transform::SetPositionTrainer(sf::Vector2f pos) {
	pos.y -= 8;
	position = pos;
}
const sf::Vector2f& C_Transform::GetPosition() const {
	return position;
}
const sf::Vector2f& C_Transform::GetPositionTrainer() const {
	sf::Vector2f currentPos = position;
	currentPos.y += 8;
	return currentPos;
}


void C_Transform::SetPositionPNJ(float x, float y) {
	position.x = x - 7;
	position.y = y - 15;
}
void C_Transform::SetPositionPNJ(sf::Vector2f pos) {
	pos.x -= 7;
	pos.y -= 15;
	position = pos;
}
const sf::Vector2f& C_Transform::GetPositionPNJ() const {
	sf::Vector2f currentPos = position;
	currentPos.x += 7;
	currentPos.y += 15;
	return currentPos;
}



void C_Transform::SetPosition(float x, float y) {
	position.x = x;
	position.y = y;
}
void C_Transform::SetPosition(sf::Vector2f pos) {
	position = pos;
}
void C_Transform::AddPosition(float x, float y) {
	position.x += x;
	position.y += y;
}
void C_Transform::AddPosition(sf::Vector2f pos) {
	position += pos;
}
void C_Transform::SetX(float x) {
	position.x = x;
}
void C_Transform::SetY(float y) {
	position.y = y;
}


