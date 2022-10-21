#pragma once
#include "component.h"
#include "../windowManager/input.h"
#include "../object/object.h"
#include "c_animation.h"


class C_KeyboardMovement : public Component
{
public:
	C_KeyboardMovement(Object* owner);
	void SetInput(Input* input);
	void SetMovementSpeed(int moveSpeed);
	void Update(float deltaTime) override;
	void Awake() override;
	void SetIdle();
private:
	int moveSpeed;
	bool isMoving;
	Input* input;
	std::shared_ptr<C_Animation> animation;
	sf::Vector2f reachPosition;
};
