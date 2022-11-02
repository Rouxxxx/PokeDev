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

void C_pnj::Awake() {
	animation = owner->GetComponent<C_Animation>();
	reachPosition = owner->transform->GetPosition();
}

bool C_pnj::move(FacingDirection dir, sf::Vector2f pos) {
	switch (dir) {
	case FacingDirection::Left:
		moveLeft(pos);
		break;
	case FacingDirection::Right:
		moveRight(pos);
		break;
	case FacingDirection::Up:
		moveUp(pos);
		break;
	case FacingDirection::Down:
		moveDown(pos);
		break;
	}

	if (reachPosition != pos)
		isMoving = true;

	return (reachPosition != pos);
}
void C_pnj::moveLeft(sf::Vector2f vec) {
	if (collider->FindLeft(vec) != -1) {
		SetAnimationState(AnimationState::IdleLeft);
		return;
	}

	vec.x -= 32;
	reachPosition = vec;
	SetAnimationState(AnimationState::WalkLeft);
}
void C_pnj::moveRight(sf::Vector2f vec) {
	if (collider->FindRight(vec) != -1) {
		SetAnimationState(AnimationState::IdleRight);
		return;
	}
	vec.x += 32;
	reachPosition = vec;
	SetAnimationState(AnimationState::WalkRight);
}
void C_pnj::moveUp(sf::Vector2f vec) {
	if (collider->FindUp(vec) != -1) {
		SetAnimationState(AnimationState::IdleUp);
		return;
	}
	vec.y -= 32;
	reachPosition = vec;
	SetAnimationState(AnimationState::WalkUp);
}
void C_pnj::moveDown(sf::Vector2f vec) {
	if (collider->FindDown(vec) != -1) {
		SetAnimationState(AnimationState::IdleDown);
		return;
	}
	vec.y += 32;
	reachPosition = vec;
	SetAnimationState(AnimationState::WalkDown);
}





void C_pnj::SetOldPosition(float x, float y) {
	SetOldPosition(sf::Vector2f(x, y));
}
void C_pnj::SetOldPosition(sf::Vector2f vec) {
	oldPosition = vec;
}