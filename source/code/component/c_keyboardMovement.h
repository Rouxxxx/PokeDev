#pragma once
#include "component.h"
#include "../windowManager/input.h"

class C_KeyboardMovement : public Component
{
public:
	C_KeyboardMovement(Object* owner);
	void SetInput(Input* input);
	void SetMovementSpeed(int moveSpeed);
	void Update(float deltaTime) override;
private:
	int moveSpeed;
	Input* input;
};
