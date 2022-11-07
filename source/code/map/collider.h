#pragma once

#include <map>
#include "../object/object.h"
#include <SFML/Graphics.hpp>


class Collider
{
public:
	Collider();
	void Add(float, float, std::shared_ptr<Object>);
	void Add(sf::Vector2f, std::shared_ptr<Object>);
	void Delete(float, float);
	void Delete(sf::Vector2f);

	std::shared_ptr<Object> FindLeft(float, float);
	std::shared_ptr<Object> FindLeft(sf::Vector2f);
	std::shared_ptr<Object> FindRight(float, float);
	std::shared_ptr<Object> FindRight(sf::Vector2f);
	std::shared_ptr<Object> FindUp(float, float);
	std::shared_ptr<Object> FindUp(sf::Vector2f);
	std::shared_ptr<Object> FindDown(float, float);
	std::shared_ptr<Object> FindDown(sf::Vector2f);
	std::shared_ptr<Object> Find(float, float);
	std::shared_ptr<Object> Find(sf::Vector2f);

	bool ExistLeft(float, float);
	bool ExistLeft(sf::Vector2f);
	bool ExistRight(float, float);
	bool ExistRight(sf::Vector2f);
	bool ExistUp(float, float);
	bool ExistUp(sf::Vector2f);
	bool ExistDown(float, float);
	bool ExistDown(sf::Vector2f);
	bool Exist(float, float);
	bool Exist(sf::Vector2f);

	void Empty();
	void SetY(float);
	float GetY();
	bool playerAbove(float);
private:
	std::map<std::pair<float, float>, std::shared_ptr<Object>> map;
	float y;
};
