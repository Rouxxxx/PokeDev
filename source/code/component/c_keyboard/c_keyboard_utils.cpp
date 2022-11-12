#include "c_keyboard.h"

void C_Keyboard::SetAnimationState(AnimationState state) {
	animation->SetAnimationState(state);
}
AnimationState C_Keyboard::GetAnimationState() {
	return animation->GetAnimationState();
}
void C_Keyboard::SetOldPosition(float x, float y) {
	SetOldPosition(sf::Vector2f(x, y));
}
void C_Keyboard::SetOldPosition(sf::Vector2f pos) {
	oldPosition = pos;
}

void C_Keyboard::Awake() {
	animation = owner->GetComponent<C_Animation>();
}

void C_Keyboard::SetIdle() {
	isMoving = false;
}

void C_Keyboard::SetInput(Input* input) {
	this->input = input;
}
void C_Keyboard::SetCollider(Collider* collider) {
	this->collider = collider;
}
void C_Keyboard::SetMovementSpeed(int moveSpeed) {
	this->moveSpeed = moveSpeed;
}

bool C_Keyboard::isDirectionKeyPressed() {
	return input->isDirectionKeyPressed();
}