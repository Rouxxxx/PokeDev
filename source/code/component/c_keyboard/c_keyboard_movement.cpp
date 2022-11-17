#include "c_keyboard.h"

void C_Keyboard::UpdateMovement(float deltaTime, sf::Vector2f currentPosition) {
	if (isMoving) animation->StartUpdating();
	else animation->StopUpdating();

	if (isInteracting) return;

	AnimationState state = animation->GetAnimationState();

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
	sf::Vector2f currentPositionBefore = sf::Vector2f(currentPosition);
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

	bool bumpingLeft = collider->ExistLeft(currentPosition);
	bool bumpingRight = collider->ExistRight(currentPosition);
	bool bumpingUp = collider->ExistUp(currentPosition);
	bool bumpingDown = collider->ExistDown(currentPosition);

	bool bumpingWall = bumpingLeft || bumpingRight || bumpingUp || bumpingDown;

	if (left && !bumpingLeft && currentFacingDir == FacingDirection::Left) {
		SetAnimationState(AnimationState::WalkLeft);
		currentPosition.x -= 32;
	} else if (left) SetAnimationState(AnimationState::IdleLeft);

	else if (right && !bumpingRight && currentFacingDir == FacingDirection::Right) {
		SetAnimationState(AnimationState::WalkRight);
		currentPosition.x += 32;
	} else if (right) SetAnimationState(AnimationState::IdleRight);

	else if (up && !bumpingUp && currentFacingDir == FacingDirection::Up) {
		SetAnimationState(AnimationState::WalkUp);
		currentPosition.y -= 32;
	} else if (up) animation->SetAnimationState(AnimationState::IdleUp);

	else if (down && !bumpingDown && currentFacingDir == FacingDirection::Down) {
		SetAnimationState(AnimationState::WalkDown);
		currentPosition.y += 32;
	} else if (down) animation->SetAnimationState(AnimationState::IdleDown);


	isMoving = (currentPosition != currentPositionBefore);

	if (!isMoving && bumpingWall) {
		soundFactory->StartSound(SoundEnum::Bump);
		return;
	}

	reachPosition = currentPosition;
	if (isMoving) {
		collider->Delete(currentPositionBefore);
		collider->Add(reachPosition, std::make_shared<Object>(owner));
	}
}