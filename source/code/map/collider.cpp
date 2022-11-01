#include "collider.h"

Collider::Collider()
	: map(std::map<std::pair<float, float>, int>())
{}


void Collider::Add(float x, float y, int tileID) {
	auto pair = std::make_pair(x, y);
	map.insert(std::pair<std::pair<float, float>, int>(pair, tileID));
}
void Collider::Add(sf::Vector2f vec, int tileID) {
	Add(vec.x, vec.y, tileID);
}

void Collider::Delete(float x, float y) {
	map.erase(std::make_pair(x, y));
}
void Collider::Delete(sf::Vector2f vec) {
	Delete(vec.x, vec.y);
}

int Collider::FindLeft(sf::Vector2f vec) { return FindLeft(vec.x, vec.y); }
int Collider::FindRight(sf::Vector2f vec) { return FindRight(vec.x, vec.y); }
int Collider::FindUp(sf::Vector2f vec) { return FindUp(vec.x, vec.y); }
int Collider::FindDown(sf::Vector2f vec) { return FindDown(vec.x, vec.y); }
int Collider::Find(sf::Vector2f vec) { return Find(vec.x, vec.y); }

int Collider::FindLeft(float x, float y) {
	x -= 32;
	return Find(x, y);
}
int Collider::FindRight(float x, float y) {
	x += 32;
	return Find(x, y);
}
int Collider::FindUp(float x, float y) {
	y -= 32;
	return Find(x, y);
}
int Collider::FindDown(float x, float y) {
	y += 32;
	return Find(x, y);
}
int Collider::Find(float x, float y) {
	auto it = map.find(std::make_pair(x, y));
	return (it != map.end()) ? it->second : -1;
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