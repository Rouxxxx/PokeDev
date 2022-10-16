#pragma once
#include "component.h"
#include "../windowManager/input.h"
#include "c_animation.h"


class C_KeyboardMovement : public Component
{
public:
	C_KeyboardMovement(Object* owner);
	void SetInput(Input* input);
	void SetMovementSpeed(int moveSpeed);
	void Update(float deltaTime) override;
	void Awake() override;
private:
	int moveSpeed;
	Input* input;
	std::shared_ptr<C_Animation> animation;
};
