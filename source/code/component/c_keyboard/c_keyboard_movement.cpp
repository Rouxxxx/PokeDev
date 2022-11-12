#include "c_keyboard.h"

void C_Keyboard::UpdateMovement(float deltaTime, sf::Vector2f currentPosition) {
	if (isInteracting)
		return;

	AnimationState state = animation->GetAnimationState();

	if (isMoving)
		animation->StartUpdating();
	else
		animation->StopUpdating();

	if (isMoving && currentPosition == reachPosition) {
		isMoving = false;

		Update(deltaTime);
		return;
	}

	if (isMoving) {
		sf::Vector2f move = animToNewPosition(state, moveSpeed);
		owner->transform->AddPosition(move);
		collider->SetY(owner->transform->GetPosition().y);

		return;
	}

	KeysToMovement(currentPosition);
}



void C_Keyboard::KeysToMovement(sf::Vector2f currentPosition) {
	sf::Vector2f currentPositionBefore = currentPosition;
	AnimationState state = GetAnimationState();
	FacingDirection currentFacingDir = animToDir(state);

	if (!isDirectionKeyPressed()) {
		SetIdle();
		return;
	}

	bool left = input->IsKeyPressed(Key::Left);
	bool right = input->IsKeyPressed(Key::Right);
	bool up = input->IsKeyPressed(Key::Up);
	bool down = input->IsKeyPressed(Key::Down);

	if (left && !collider->ExistLeft(currentPosition) && currentFacingDir == FacingDirection::Left) {
		SetAnimationState(AnimationState::WalkLeft);
		currentPosition.x -= 32;
	}
	else if (left)
		SetAnimationState(AnimationState::IdleLeft);

	else if (right && !collider->ExistRight(currentPosition) && currentFacingDir == FacingDirection::Right) {
		SetAnimationState(AnimationState::WalkRight);
		currentPosition.x += 32;
	}
	else if (right)
		SetAnimationState(AnimationState::IdleRight);

	else if (up && !collider->ExistUp(currentPosition) && currentFacingDir == FacingDirection::Up) {
		SetAnimationState(AnimationState::WalkUp);
		currentPosition.y -= 32;
	}
	else if (up)
		animation->SetAnimationState(AnimationState::IdleUp);

	else if (down && !collider->ExistDown(currentPosition) && currentFacingDir == FacingDirection::Down) {
		SetAnimationState(AnimationState::WalkDown);
		currentPosition.y += 32;
	}
	else if (down)
		animation->SetAnimationState(AnimationState::IdleDown);

	isMoving = (currentPosition != currentPositionBefore);
	reachPosition = currentPosition;
	if (isMoving) {
		collider->Delete(currentPositionBefore);
		collider->Add(reachPosition, std::make_shared<Object>(owner));
	}
}