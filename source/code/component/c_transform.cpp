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
const sf::Vector2f& C_Transform::GetPosition() const {
	return position;
}
const sf::Vector2f& C_Transform::GetPositionTrainer() const {
	return position + sf::Vector2f(0, 8);
}

