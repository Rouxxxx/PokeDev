#pragma once
#include "../../component/component.h"
#include "../../component/c_animation.h"
#include "../../component/c_textbox.h"
#include "../../windowManager/input.h"
#include "../../object/object.h"

#include "../../map/collider.h"

class C_KeyboardMovement : public Component
{
public:
	C_KeyboardMovement(Object* owner);
	void SetInput(Input* input);
	void SetCollider(Collider* collider);
	void SetMovementSpeed(int moveSpeed);
	void Update(float deltaTime) override;
	void KeysToMovement(sf::Vector2f);
	void Awake() override;
	void SetIdle();
	void SetOldPosition(float, float);
	void SetOldPosition(sf::Vector2f);
	bool isDirectionKeyPressed();
private:
	AnimationState GetAnimationState();
	void SetAnimationState(AnimationState state);
	int moveSpeed;
	bool isMoving;
	Input* input;
	Collider* collider;
	std::shared_ptr<C_Animation> animation;
	std::shared_ptr<C_TextBox> textBox;
	sf::Vector2f reachPosition;
	sf::Vector2f oldPosition;
};
