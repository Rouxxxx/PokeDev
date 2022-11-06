#pragma once
#include "component.h"

class C_Transform : public Component
{
public:
	C_Transform(Object* owner);
	void SetPositionTrainer(float x, float y);
	void SetPositionTrainer(sf::Vector2f pos);
	void SetPositionPNJ(float x, float y);
	void SetPositionPNJ(sf::Vector2f pos);
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f pos);
	void AddPosition(float x, float y);
	void AddPosition(sf::Vector2f pos);
	void SetX(float x);
	void SetY(float y);
	const sf::Vector2f& GetPosition() const;
	const sf::Vector2f& GetPositionTrainer() const;
	const sf::Vector2f& GetPositionPNJ() const;
	void SetStatic(bool isStatic);
	bool isStatic() const;

private:
	sf::Vector2f position;
	bool isStaticTransform;

};
