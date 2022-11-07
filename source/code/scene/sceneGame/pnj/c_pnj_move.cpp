#include "c_pnj.h"

#include <iostream>
void C_pnj::UpdateMove(float deltaTime) {
	if (!isMoving) {
		return;
	}

	AnimationState state = animation->GetAnimationState();

	animation->StartUpdating();

	if (currentPosition == reachPosition) {
		isMoving = false;
		if (waits.at(currentActionId) <= 0.0f)
			(this->*(this->behavior))();
		return;
	}

	sf::Vector2f move = animToNewPosition(state, moveSpeed);
	owner->transform->AddPosition(move);
}




bool C_pnj::move(FacingDirection dir) {
	switch (dir) {
	case FacingDirection::Left:
		movementLeft();
		break;
	case FacingDirection::Right:
		movementRight();
		break;
	case FacingDirection::Up:
		movementUp();
		break;
	case FacingDirection::Down:
		movementDown();
		break;
	}

	if (reachPosition != currentPosition) {
		collider->Delete(oldPosition);
		oldPosition = animToReachPosition(oldPosition, GetAnimationState());
		collider->Add(oldPosition, std::make_shared<Object>(owner));
		isMoving = true;
	}

	return (reachPosition != currentPosition);
}

bool C_pnj::moveLeft() {
	return move(FacingDirection::Left);
}
void C_pnj::movementLeft() {
	if (collider->ExistLeft(currentPosition)) {
		SetAnimationState(AnimationState::IdleLeft);
		return;
	}

	reachPosition = currentPosition + sf::Vector2f(-32, 0);
	SetAnimationState(AnimationState::WalkLeft);
}


bool C_pnj::moveRight() {
	return move(FacingDirection::Right);
}
void C_pnj::movementRight() {
	if (collider->ExistRight(currentPosition)) {
		SetAnimationState(AnimationState::IdleRight);
		return;
	}
	reachPosition = currentPosition + sf::Vector2f(32, 0);
	SetAnimationState(AnimationState::WalkRight);
}


bool C_pnj::moveUp() {
	return move(FacingDirection::Up);
}
void C_pnj::movementUp() {
	if (collider->ExistUp(currentPosition)) {
		SetAnimationState(AnimationState::IdleUp);
		return;
	}
	reachPosition = currentPosition + sf::Vector2f(0, -32);
	SetAnimationState(AnimationState::WalkUp);
}



bool C_pnj::moveDown() {
	return move(FacingDirection::Down);
}
void C_pnj::movementDown() {
	if (collider->ExistDown(currentPosition)) {
		SetAnimationState(AnimationState::IdleDown);
		return;
	}
	reachPosition = currentPosition + sf::Vector2f(0, 32);
	SetAnimationState(AnimationState::WalkDown);
}