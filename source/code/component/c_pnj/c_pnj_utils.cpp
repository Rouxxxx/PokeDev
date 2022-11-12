#include "c_pnj.h"

void C_pnj::SetCollider(Collider* collider) {
	this->collider = collider;
}
void C_pnj::SetMovementSpeed(int moveSpeed) {
	this->moveSpeed = moveSpeed;
}

void C_pnj::SetAnimationState(AnimationState state) {
	animation->SetAnimationState(state);
}
AnimationState C_pnj::GetAnimationState() {
	return animation->GetAnimationState();
}

void C_pnj::SetSpritePtr(std::shared_ptr<C_Sprite> newSpritePtr) {
	spritePtr = newSpritePtr;
}

void C_pnj::SetOldPosition(float x, float y) {
	SetOldPosition(sf::Vector2f(x, y));
}
void C_pnj::SetOldPosition(sf::Vector2f vec) {
	oldPosition = vec;
}


bool C_pnj::IdleLeftBool() {
	SetAnimationState(AnimationState::IdleLeft);
	return true;
}
bool C_pnj::IdleRightBool() {
	SetAnimationState(AnimationState::IdleRight);
	return true;
}
bool C_pnj::IdleUpBool() {
	SetAnimationState(AnimationState::IdleUp);
	return true;
}
bool C_pnj::IdleDownBool() {
	SetAnimationState(AnimationState::IdleDown);
	return true;
}

void C_pnj::Idle() { SetAnimationState(AnimationState::IdleDown); }
void C_pnj::IdleLeft() { SetAnimationState(AnimationState::IdleLeft); }
void C_pnj::IdleRight() { SetAnimationState(AnimationState::IdleRight); }
void C_pnj::IdleUp() { SetAnimationState(AnimationState::IdleUp); }
void C_pnj::IdleDown() { SetAnimationState(AnimationState::IdleDown); }