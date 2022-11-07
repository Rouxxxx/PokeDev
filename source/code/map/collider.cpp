#include "collider.h"

Collider::Collider()
	: map(std::map<std::pair<float, float>, std::shared_ptr<Object>>()), y(-1)
{}


void Collider::Add(float x, float y, std::shared_ptr<Object> obj) {
	auto pair = std::make_pair(x, y);
	map.insert(std::pair<std::pair<float, float>, std::shared_ptr<Object>>(pair, obj));
}
void Collider::Add(sf::Vector2f vec, std::shared_ptr<Object> obj) {
	Add(vec.x, vec.y, obj);
}

void Collider::Delete(float x, float y) {
	map.erase(std::make_pair(x, y));
}
void Collider::Delete(sf::Vector2f vec) {
	Delete(vec.x, vec.y);
}

std::shared_ptr<Object> Collider::FindLeft(sf::Vector2f vec) { return FindLeft(vec.x, vec.y); }
std::shared_ptr<Object> Collider::FindRight(sf::Vector2f vec) { return FindRight(vec.x, vec.y); }
std::shared_ptr<Object> Collider::FindUp(sf::Vector2f vec) { return FindUp(vec.x, vec.y); }
std::shared_ptr<Object> Collider::FindDown(sf::Vector2f vec) { return FindDown(vec.x, vec.y); }
std::shared_ptr<Object> Collider::Find(sf::Vector2f vec) { return Find(vec.x, vec.y); }

std::shared_ptr<Object> Collider::FindLeft(float x, float y) {
	x -= 32;
	return Find(x, y);
}
std::shared_ptr<Object> Collider::FindRight(float x, float y) {
	x += 32;
	return Find(x, y);
}
std::shared_ptr<Object> Collider::FindUp(float x, float y) {
	y -= 32;
	return Find(x, y);
}
std::shared_ptr<Object> Collider::FindDown(float x, float y) {
	y += 32;
	return Find(x, y);
}
std::shared_ptr<Object> Collider::Find(float x, float y) {
	auto it = map.find(std::make_pair(x, y));
	return (it != map.end()) ? it->second : nullptr;
}


bool Collider::ExistLeft(sf::Vector2f vec) { return ExistLeft(vec.x, vec.y); }
bool Collider::ExistRight(sf::Vector2f vec) { return ExistRight(vec.x, vec.y); }
bool Collider::ExistUp(sf::Vector2f vec) { return ExistUp(vec.x, vec.y); }
bool Collider::ExistDown(sf::Vector2f vec) { return ExistDown(vec.x, vec.y); }
bool Collider::Exist(sf::Vector2f vec) { return Exist(vec.x, vec.y); }

bool Collider::ExistLeft(float x, float y) {
	x -= 32;
	return Exist(x, y);
}
bool Collider::ExistRight(float x, float y) {
	x += 32;
	return Exist(x, y);
}
bool Collider::ExistUp(float x, float y) {
	y -= 32;
	return Exist(x, y);
}
bool Collider::ExistDown(float x, float y) {
	y += 32;
	return Exist(x, y);
}
bool Collider::Exist(float x, float y) {
	auto it = map.find(std::make_pair(x, y));
	return (it != map.end());
}


void Collider::Empty() {
	map.clear();
}

void Collider::SetY(float newY) {
	y = newY;
}
float Collider::GetY() {
	return y;
}


bool Collider::playerAbove(float yCmp) {
	return y > yCmp;
}